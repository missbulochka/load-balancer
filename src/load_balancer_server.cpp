#include "load_balancer_server.h"
#include <sys/socket.h>
#include <iostream>
#include <csignal>

load_balancer_server::load_balancer_server()
    : sockfd()
    , port(5000)
    , datagram()
    , client_addr{}
    , client_addr_len(sizeof(client_addr))
    , server_addr{AF_INET, htons(port), INADDR_ANY} {
    start_server();
}

void load_balancer_server::signal_handler(int signal_num) {
    std::cout << "Interrupt signal (" << signal_num << "reveived\n";
    exit(signal_num);
}

void load_balancer_server::start_server() {
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (bind(sockfd, reinterpret_cast<const struct sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    signal(SIGTERM, signal_handler);
}

void load_balancer_server::recv_datagram() {
    while (true) {
        if (recvfrom(0,
                     reinterpret_cast<void*>(datagram),
                     sizeof(datagram),
                     MSG_WAITALL,
                     reinterpret_cast<struct sockaddr*>(&client_addr),
                     &client_addr_len)
            == -1) {
            perror("Error receiving datagram from socket");
            continue;
        }
        std::cout << "Datagram received\n";
    }
}
