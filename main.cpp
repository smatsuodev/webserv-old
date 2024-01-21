#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include "IOTask.hpp"

using namespace std;

void handleHangUp() {
	cout << "-> disconnected" << endl;
}

void handleConnection(int fd, SockAddrIn addr, socklen_t addr_len, IOTaskManager &m) {
	char dst[INET_ADDRSTRLEN];

	inet_ntop(AF_INET, &addr, dst, addr_len);
	cout << "<- connection from " << dst << endl;

	CloseFactory hangUp(handleHangUp);
	m.createIOTask(hangUp, fd);
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
	AcceptFactory acceptConnection(handleConnection);

	taskManager.createIOTask(acceptConnection, sock);

	taskManager.executeTasks();

//	while (true) {
//		poll(&fds[0], fds.size(), -1);
//
//		if (fds[0].revents == POLLIN) {
//			int conn_fd = accept(sock, nullptr, nullptr);
//			struct pollfd conn = {0};
//			conn.fd = conn_fd;
//			conn.events = POLLIN | POLLOUT;
//			if (available_fd_index.empty()) {
//				fds.push_back(conn);
//			} else {
//				int index = available_fd_index.top();
//				available_fd_index.pop();
//
//				fds[index] = conn;
//			}
//			cout << "<- connection: fd=" << conn.fd << ", poll_fds.size=" << fds.size()
//				 << ", stack.size="
//				 << available_fd_index.size() << endl;
//		} else {
//			for (int i = 1; i < fds.size(); i++) {
//				if (fds[i].revents & POLLHUP) {
//					close(fds[i].fd);
//					available_fd_index.push(i);
//					cout << "-> disconnection: fd=" << fds[i].fd << ", poll_fds.size=" << fds.size()
//						 << ", stack.size="
//						 << available_fd_index.size() << endl;
//					fds[i].fd = -1;
//					break;
//				}
//			}
//		}
//	}
}
