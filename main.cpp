#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include "IOTask.hpp"

using namespace std;

class CloseConnectionCallback : public WriteFileCallback {
	int connection;

public:
	explicit CloseConnectionCallback(int connection) : connection(connection) {}

	void trigger() {
		close(connection);
	}
};

class EchoCallback : public ReadFileCallback {
	IOTaskManager &m;
	int dst;

public:
	explicit EchoCallback(IOTaskManager &m, int dst) : m(m), dst(dst) {}

	void trigger(std::string fileData) {
		new WriteFile(m, dst, fileData, new CloseConnectionCallback(dst));
	}
};

class EstablishConnectionCallback : public AcceptCallback {
	IOTaskManager &m;
public :
	explicit EstablishConnectionCallback(IOTaskManager &m) : m(m) {}

	void trigger(int connection, SockAddrIn addr) {
		cout << "<- connection from " << inet_ntoa(addr.sin_addr) << endl;

		new ReadFile(m, connection, new EchoCallback(m, connection));
	}
};

int main() {
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET; //アドレスファミリ(ipv4)
	addr.sin_port = htons(1234); //ポート番号,htons()関数は16bitホストバイトオーダーをネットワークバイトオーダーに変換
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //IPアドレス,inet_addr()関数はアドレスの翻訳

	bind(sock, (struct sockaddr *) &addr, sizeof(addr));
	listen(sock, SOMAXCONN);

	IOTaskManager taskManager;

	new Accept(taskManager, sock, new EstablishConnectionCallback(taskManager));
	taskManager.executeTasks();
	return 0;
}
