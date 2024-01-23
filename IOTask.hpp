#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <list>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <poll.h>
#include <stdnoreturn.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define NOT_MONITORED (-1)
#define READ_FILE_READ_SIZE (size_t)4096
#define WRITE_FILE_WRITE_SIZE (size_t)4096

typedef struct pollfd PollFd;
typedef struct sockaddr SockAddr;
typedef struct sockaddr_in SockAddrIn;
typedef std::map<std::pair<int, short>, int> TaskIndexMap;

class IOTask;

class IOTaskManager {
	TaskIndexMap task_index_map;
	std::vector<PollFd> poll_fds;
	std::vector<IOTask *> tasks;
	std::stack<unsigned long> vacant_slots;

public:
	void add(IOTask *task);
	void remove(IOTask *task);
	void executeTasks();
};

class IOTask {
public:
	const int fd;
	const short events;
	IOTask(int fd, short events);
	virtual ~IOTask();
	virtual void execute(IOTaskManager &m) = 0;
};

class IOCallback {
public:
	virtual ~IOCallback();
};

class IReadFileCallback : public IOCallback {
public:
	virtual void trigger(std::string fileData, IOTaskManager &m) = 0;
};

class ReadFile : public IOTask {
	IReadFileCallback *callback;
	char *tmp_buf[READ_FILE_READ_SIZE];
	std::string read_buf;

public:
	ReadFile(int fd, IReadFileCallback *callback);
	~ReadFile();
	void execute(IOTaskManager &m);
};

class IWriteFileCallback : public IOCallback {
public:
	virtual void trigger() = 0;
};

class WriteFile : public IOTask {
	IWriteFileCallback *callback;
	std::string dataToWrite;
	const char *buf;
	size_t buf_len;

public:
	WriteFile(int fd, const std::string &dataToWrite, IWriteFileCallback *callback);
	void execute(IOTaskManager &m);
};

class IAcceptCallback : public IOCallback {
public:
	virtual void trigger(int connection, SockAddrIn addr, IOTaskManager &m) = 0;
};

class Accept : public IOTask {
	IAcceptCallback *callback;
	SockAddrIn sock_addr;
	socklen_t sock_addr_len;

public:
	Accept(int socket, IAcceptCallback *callback);
	~Accept();
	void execute(IOTaskManager &m);
};

#endif
