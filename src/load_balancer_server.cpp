#include "load_balancer_server.h"
#include "balancer.h"
#include <sys/socket.h>
#include <iostream>
#include <csignal>

load_balancer_server::load_balancer_server()
    : sockfd()
    , port(50055)
    , datagram()
    , client_addr_len(sizeof(client_addr))
    , client_addr{}
    , server_addr{AF_INET, htons(port), INADDR_ANY} {}

void load_balancer_server::create_socket() {
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Socket successfully created\n";
}

void load_balancer_server::bind_socket() {
    server_addr.sin_port = htons(port);
    if (bind(sockfd, reinterpret_cast<const struct sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Socket successfully bound\n";
}

std::string load_balancer_server::recv_datagram() {
    if (recvfrom(sockfd,
                 reinterpret_cast<void*>(&datagram),
                 sizeof(datagram),
                 MSG_WAITALL,
                 reinterpret_cast<struct sockaddr*>(&client_addr),
                 &client_addr_len)
        == -1) {
        perror("Error receiving datagram from socket");
        return "";
    }
    return datagram;
}

void load_balancer_server::start_server(std::uint16_t recv_port) {
    port = recv_port;
    create_socket();
    bind_socket();
}

void load_balancer_server::stop_server() {
    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
}
