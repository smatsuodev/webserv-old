#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include "IOTask.hpp"

using namespace std;

void handleHangUp(SockAddrIn addr, socklen_t addr_len) {
	char dst[INET_ADDRSTRLEN];

	inet_ntop(AF_INET, &addr, dst, addr_len);
	cout << "-> disconnection of " << dst << endl;
}

void handleConnection(int fd, SockAddrIn addr, socklen_t addr_len, IOTaskManager &m) {
	char dst[INET_ADDRSTRLEN];

	inet_ntop(AF_INET, &addr, dst, addr_len);
	cout << "<- connection from " << dst << endl;

	m.add(new Close(fd, new CloseCallback(handleHangUp, addr, addr_len)));
}

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

	taskManager.add(new Accept(sock, new AcceptCallback(handleConnection)));
	taskManager.executeTasks();
}
