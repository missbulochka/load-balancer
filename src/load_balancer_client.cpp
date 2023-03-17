#include "load_balancer_client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <csignal>

load_balancer_client::load_balancer_client()
    : sockfd()
    , port(5001)
    , datagram()
    , server_addr{AF_INET, htons(port), INADDR_ANY} {}

void load_balancer_client::signal_handler(int signal_num) {
    std::cout << "Interrupt signal (" << signal_num << ") received\n";
    exit(signal_num);
}

void load_balancer_client::create_socket() {
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Socket successfully created\n";
}

void load_balancer_client::send_datagram() {
    // datagram = server.datagram;
    /* get_addr
     if (inet_aton("127.0.0.1", &server_addr.sin_addr) == 0) {
        perror("inet_aton() failed");
    } */

    while (true) {
        sleep(1);
        if (sendto(sockfd,
                   reinterpret_cast<const void*>(&datagram),
                   datagram.size(),
                   MSG_CONFIRM,
                   reinterpret_cast<const struct sockaddr*>(&server_addr),
                   sizeof(server_addr))
            == -1) {
            perror("Error receiving datagram from socket");
            continue;
        }
    }
}

void load_balancer_client::start_client() {
    create_socket();
    signal(SIGTERM, signal_handler);
    send_datagram();
}

void load_balancer_client::stop_client() {
    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
}
