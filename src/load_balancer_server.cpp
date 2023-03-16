#include "load_balancer_server.h"
#include <sys/socket.h>
#include <iostream>
#include <csignal>

load_balancer_server::load_balancer_server()
    : sockfd()
    , port(5000)
    , datagram()
    , client_addr_len(sizeof(client_addr))
    , client_addr{}
    , server_addr{AF_INET, htons(port), INADDR_ANY} {}

void load_balancer_server::signal_handler(int signal_num) {
    std::cout << "Interrupt signal (" << signal_num << ") received\n";
    exit(signal_num);
}

void load_balancer_server::create_socket() {
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Socket successfully created\n";
}

void load_balancer_server::bind_socket() {
    // port = config.get_port();
    // server_addr.sin_port = htons(port);
    if (bind(sockfd, reinterpret_cast<const struct sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Socket successfully bound\n";
}

void load_balancer_server::recv_datagram() {
    while (true) {
        if (recvfrom(sockfd,
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

void load_balancer_server::start_server() {
    create_socket();
    bind_socket();
    signal(SIGTERM, signal_handler);
    recv_datagram();
}
