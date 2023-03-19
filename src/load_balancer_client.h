#ifndef LOAD_BALANCER_LOAD_BALANCER_CLIENT_H
#define LOAD_BALANCER_LOAD_BALANCER_CLIENT_H

#include <cstdint>
#include <string>
#include <netinet/in.h>

class load_balancer_client {
public:
    load_balancer_client();
    void start_client();
    void send_datagram(std::pair<std::string, std::uint16_t> recv_worker, std::string recv_datagram);
    void stop_client();

private:
    int sockfd;
    struct sockaddr_in server_addr;

    void create_socket();
};


#endif  //LOAD_BALANCER_LOAD_BALANCER_CLIENT_H
