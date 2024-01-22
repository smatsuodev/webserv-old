#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include "IOTask.hpp"

using namespace std;

class CloseConnectionCallback : public IWriteFileCallback {
	int connection;

public:
	CloseConnectionCallback(int connection) : connection(connection) {}

	void trigger() {
		close(connection);
	}
};

class EchoCallback : public IReadFileCallback {
	int dst;

public:
	explicit EchoCallback(int dst) : dst(dst) {}

	void trigger(std::string fileData, IOTaskManager &m) {
		m.add(new WriteFile(dst, fileData, new CloseConnectionCallback(dst)));
	}
};

class AcceptCallback : public IAcceptCallback {
public :
	AcceptCallback() {}

	void trigger(int connection, SockAddrIn addr, IOTaskManager &m) {
		cout << "<- connection from " << inet_ntoa(addr.sin_addr) << endl;

		m.add(new ReadFile(connection, new EchoCallback(connection)));
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

	taskManager.add(new Accept(sock, new AcceptCallback()));
	taskManager.executeTasks();
	return 0;
}
