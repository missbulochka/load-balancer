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
    const std::string* server_response;
    std::string client_response[1024];

    struct sockaddr_in client_addr;

    struct sockaddr_in server_addr {
        AF_INET, htons(port), INADDR_ANY,
    };
};


#endif  //LOAD_BALANCER_LOAD_BALANCER_SERVER_H
