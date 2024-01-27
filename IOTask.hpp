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

	static std::pair<int, short> getKey(IOTask *task);
public:
	void add(IOTask *task);
	void remove(IOTask *task);
	void executeTasks();
};

typedef enum {
	PAUSE,
	REMOVE,
} IOTaskResult;

class IOTask {
	IOTaskManager &m;

public:
	const int fd;
	const short events;
	IOTask(IOTaskManager &m, int fd, short events);
	virtual ~IOTask();
	virtual IOTaskResult execute() = 0;
};

class IOCallback {
public:
	virtual ~IOCallback();
};

class ReadFileCallback : public IOCallback {
public:
	virtual void trigger(std::string file_data) = 0;
};

class ReadFile : public IOTask {
	ReadFileCallback *callback;
	char *tmp_buf[READ_FILE_READ_SIZE];
	std::string read_buf;

public:
	ReadFile(IOTaskManager &m, int fd, ReadFileCallback *callback);
	~ReadFile();
	IOTaskResult execute();
};

class WriteFileCallback : public IOCallback {
public:
	virtual void trigger() = 0;
};

class WriteFile : public IOTask {
	WriteFileCallback *callback;
	std::string dataToWrite;
	const char *buf;
	size_t buf_len;

public:
	WriteFile(IOTaskManager &m, int fd, const std::string &data_to_write,
			  WriteFileCallback *callback);
	IOTaskResult execute();
};

class AcceptCallback : public IOCallback {
public:
	virtual void trigger(int connection, SockAddrIn addr) = 0;
};

class Accept : public IOTask {
	AcceptCallback *callback;
	SockAddrIn sock_addr;
	socklen_t sock_addr_len;

public:
	Accept(IOTaskManager &m, int socket, AcceptCallback *callback);
	~Accept();
	IOTaskResult execute();
};

#endif
