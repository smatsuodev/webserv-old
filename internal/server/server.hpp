#ifndef SERVER_HPP
#define SERVER_HPP

class Server {
public:
    Server();
    Server(const Server &other);
    ~Server();
    Server &operator=(const Server &other);
    void start(void);

private:
    int createServerSocket();
};

#endif
