#ifndef LOAD_BALANCER_LOAD_BALANCER_SERVER_H
#define LOAD_BALANCER_LOAD_BALANCER_SERVER_H

#include <cstdint>
#include <string>
#include <netinet/in.h>

class load_balancer_server {
public:
    explicit load_balancer_server();
    void start_server(std::uint16_t port);
    void stop_server();

private:
    int sockfd;
    std::uint16_t port;
    std::string datagram[1024];
    socklen_t client_addr_len;
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;

    static void signal_handler(int signum);
    void create_socket();
    void bind_socket();
    void recv_datagram();
};


#endif  //LOAD_BALANCER_LOAD_BALANCER_SERVER_H
