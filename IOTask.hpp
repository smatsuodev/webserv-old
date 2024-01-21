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
	void remove(int fd, short events);
	noreturn void executeTasks();
};

class IOTask {
public:
	const int fd;
	const short events;
	IOTask(int fd, short events);
	virtual ~IOTask();
	virtual void execute(IOTaskManager &m) = 0;
};

class ReadFile : public IOTask {
	typedef void (*Callback)(const std::string &);

	Callback callback;
	char *tmp_buf[READ_FILE_READ_SIZE];
	std::string read_buf;

public:
	ReadFile(int fd, Callback callback);
	void execute(IOTaskManager &m);
};

class WriteFile : public IOTask {
	typedef void (*Callback)();

	Callback callback;
	const char *buf;
	size_t buf_len;

public:
	WriteFile(int fd, const std::string &dataToWrite, Callback callback);
	void execute(IOTaskManager &m);
};

class Accept : public IOTask {
	typedef void (*Callback)(int, SockAddrIn, socklen_t, IOTaskManager &);

	Callback callback;
	SockAddrIn sock_addr;
	socklen_t sock_addr_len;

public:
	Accept(int socket, Callback callback);
	void execute(IOTaskManager &m);
};

class Close : public IOTask {
	typedef void (*Callback)();

	Callback callback;

public:
	Close(int fd, Callback callback);
	void execute(IOTaskManager &m);
};

#endif
