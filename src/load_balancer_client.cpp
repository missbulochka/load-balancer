#include "load_balancer_client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <csignal>

load_balancer_client::load_balancer_client()
    : sockfd()
    , server_addr{AF_INET, htons(5055), INADDR_ANY} {}

void load_balancer_client::create_socket() {
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed (client)");
        exit(EXIT_FAILURE);
    }
    std::cout << "Socket successfully created\n";
}

void load_balancer_client::send_datagram(std::pair<std::string, std::uint16_t> recv_worker, std::string recv_datagram) {
    if (inet_aton(reinterpret_cast<const char*>(&recv_worker.first[0]), &server_addr.sin_addr) == 0) {
        perror("inet_aton() failed");
    }
    server_addr.sin_port = htons(recv_worker.second);
    if (sendto(sockfd,
               reinterpret_cast<const void*>(&recv_datagram),
               recv_datagram.size(),
               0,
               reinterpret_cast<const struct sockaddr*>(&server_addr),
               sizeof(server_addr))
        == -1) {
        perror("Error receiving datagram from socket");
    }
}

void load_balancer_client::start_client() {
    create_socket();
}

void load_balancer_client::stop_client() {
    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
}
