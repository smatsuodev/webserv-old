#include "IOTask.hpp"
#include <unistd.h>
#include <stdnoreturn.h>
#include <sys/socket.h>

void IOTaskManager::add(IOTask *task) {
	std::pair<int, short> key = std::pair<int, short>(task->fd, task->events);
	TaskIndexMap::iterator it = task_index_map.find(key);
	if (it != task_index_map.end() && it->second != NOT_MONITORED)
		return; // TODO:例外を返す

	if (vacant_slots.empty()) {
		PollFd poll_fd;
		poll_fd.fd = task->fd;
		poll_fd.events = task->events;

		poll_fds.push_back(poll_fd);
		tasks.push_back(task);

		task_index_map[key] = poll_fds.size() - 1;
	} else {
		unsigned long index = vacant_slots.top();
		vacant_slots.pop();

		poll_fds[index].fd = task->fd;
		poll_fds[index].events = task->events;
		tasks[index] = task;
	}
}

void IOTaskManager::createIOTask(IOTaskFactory &factory, int fd) {
	IOTask *task = factory.create(fd);

	add(task);
}

void IOTaskManager::remove(int fd, short events) {
	std::pair<int, short> key = std::pair<int, short>(fd, events);
	TaskIndexMap::iterator it = task_index_map.find(key);
	if (it == task_index_map.end() || it->second == NOT_MONITORED)
		return;
	int *index = &it->second;

	poll_fds[*index].fd = NOT_MONITORED;
	delete tasks[*index];
	vacant_slots.push(*index);
	*index = NOT_MONITORED;
}

noreturn void IOTaskManager::executeTasks() {
	while (true) {
		poll(&poll_fds[0], poll_fds.size(), -1);

		for (unsigned long i = 0; i < poll_fds.size(); i++) {
			PollFd *poll_fd = &poll_fds[i];
			if (poll_fd->fd == NOT_MONITORED)
				continue;

			IOTask *task = tasks[i];
			if (poll_fd->revents & task->events)
				task->execute(*this);
		}
	}
}

IOTask::IOTask(int fd, short events) : fd(fd), events(events) {}

IOTask::~IOTask() {}

ReadFile::ReadFile(int fd, Callback callback) : IOTask(fd, POLLIN), callback(callback) {
	memset(tmp_buf, 0, READ_FILE_READ_SIZE);
}

void ReadFile::execute(IOTaskManager &m) {
	ssize_t read_size = read(fd, tmp_buf, READ_FILE_READ_SIZE);

	if (read_size == 0) {
		callback(read_buf);
		m.remove(fd, events);
		return;
	}
	read_buf.append((const char *) tmp_buf);
}

ReadFileFactory::ReadFileFactory(ReadFile::Callback callback) : callback(callback) {}

ReadFile *ReadFileFactory::create(int fd) {
	return new ReadFile(fd, callback);
}

WriteFile::WriteFile(int fd, const std::string &dataToWrite, Callback callback)
	: IOTask(fd, POLLOUT), callback(callback) {
	this->buf = dataToWrite.c_str();
	this->buf_len = dataToWrite.length();
}

void WriteFile::execute(IOTaskManager &m) {
	ssize_t written_size = write(fd, buf, std::min(WRITE_FILE_WRITE_SIZE, buf_len));
	buf += written_size;
	buf_len -= buf_len;

	if (buf_len == 0) {
		callback();
		m.remove(fd, events);
	}
}

WriteFileFactory::WriteFileFactory(const std::string &dataToWrite, WriteFile::Callback callback)
	: dataToWrite(dataToWrite), callback(callback) {}

WriteFile *WriteFileFactory::create(int fd) {
	return new WriteFile(fd, dataToWrite, callback);
}

Accept::Accept(int socket, Callback callback) : IOTask(socket, POLLIN), callback(callback) {}

void Accept::execute(IOTaskManager &m) {
	int connection = accept(fd, (SockAddr *) &sock_addr, &sock_addr_len);
	callback(connection, sock_addr, sock_addr_len, m);
}

AcceptFactory::AcceptFactory(Accept::Callback callback) : callback(callback) {}

Accept *AcceptFactory::create(int fd) {
	return new Accept(fd, callback);
}

Close::Close(int fd, Callback callback) : IOTask(fd, POLLHUP), callback(callback) {}

void Close::execute(IOTaskManager &m) {
	close(fd);
	callback();
	m.remove(fd, events);
}

CloseFactory::CloseFactory(Close::Callback callback) : callback(callback) {}

Close *CloseFactory::create(int fd) {
	return new Close(fd, callback);
}
