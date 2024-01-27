#include "HTTPServer.hpp"
#include <arpa/inet.h>
#include <iostream>

class ReadRequestCallback : public ReadFileCallback {
	IOTaskManager &m;
	int client_fd;
	Handler *handler;

public:
	ReadRequestCallback(IOTaskManager &m, int client_fd, Handler *handler)
		: m(m), client_fd(client_fd), handler(handler) {}

	void trigger(std::string raw_request) {
		Context context = Context(m, client_fd, raw_request);

		handler->trigger(context);
	}
};

class EstablishConnectionCallback : public AcceptCallback {
	IOTaskManager &m;
	Handler *handler;

public :
	EstablishConnectionCallback(IOTaskManager &m, Handler *handler)
		: m(m), handler(handler) {}

	void trigger(int client_fd, SockAddrIn addr) {
		std::cout << "<- client_fd from " << inet_ntoa(addr.sin_addr) << std::endl;

		new ReadFile(m, client_fd, new ReadRequestCallback(m, client_fd, handler));
	}
};

HTTPServer::HTTPServer(const std::string &host, int port) : host(host), port(port) {}

void HTTPServer::start(Handler *handler) {
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET; //アドレスファミリ(ipv4)
	addr.sin_port = htons(port); //ポート番号,htons()関数は16bitホストバイトオーダーをネットワークバイトオーダーに変換
	addr.sin_addr.s_addr = inet_addr(host.c_str()); //IPアドレス,inet_addr()関数はアドレスの翻訳

	bind(sock, (struct sockaddr *) &addr, sizeof(addr));
	listen(sock, SOMAXCONN);
	new Accept(taskManager, sock, new EstablishConnectionCallback(taskManager, handler));
}
