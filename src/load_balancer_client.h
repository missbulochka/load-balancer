#ifndef LOAD_BALANCER_LOAD_BALANCER_CLIENT_H
#define LOAD_BALANCER_LOAD_BALANCER_CLIENT_H

#include <cstdint>
#include <string>
#include <netinet/in.h>

class load_balancer_client {
public:
    load_balancer_client();
    void start_client();
    void stop_client();

private:
    int sockfd;
    std::uint16_t port;
    std::string datagram;
    struct sockaddr_in server_addr;

    static void signal_handler(int signum);
    void create_socket();
    void send_datagram();
};


#endif  //LOAD_BALANCER_LOAD_BALANCER_CLIENT_H
