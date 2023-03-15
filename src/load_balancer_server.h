#ifndef LOAD_BALANCER_LOAD_BALANCER_SERVER_H
#define LOAD_BALANCER_LOAD_BALANCER_SERVER_H

#include <cstdint>
#include <string>
#include <netinet/in.h>

class load_balancer_server {
public:
    load_balancer_server();
    void recv_datagram();

private:
    int sockfd;
    std::uint16_t port;
    std::string datagram[1024];
    struct sockaddr_in client_addr;
    socklen_t client_addr_len;
    struct sockaddr_in server_addr;

    void start_server();
};


#endif  //LOAD_BALANCER_LOAD_BALANCER_SERVER_H
