#ifndef SERVER_HPP
#define SERVER_HPP

#include "IOTask.hpp"
#include <vector>

class Context {
public:
	Context(IOTaskManager &m, int client_fd, const std::string &raw_request);
};

class Handler {
public:
	virtual void trigger(Context &context) = 0;
};

class HTTPServer {
	IOTaskManager taskManager;
	const std::string &host;
	int port;

public:
	HTTPServer(const std::string &host, int port);
	void start(Handler *handler);
};

#endif
