#include "load_balancer_client.h"
<<<<<<< HEAD
#include <sys/socket.h>
#include <iostream>
#include <csignal>

load_balancer_client::load_balancer_client()
    : sockfd()
    , port(5001)
    , datagram()
    , server_addr{AF_INET, htons(port), INADDR_ANY} {}

void load_balancer_client::close_socket() {}

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
    while (true) {
        sendto(sockfd,
               reinterpret_cast<const void*>(&datagram),
               sizeof(datagram),
               MSG_CONFIRM,
               reinterpret_cast<const struct sockaddr*>(&server_addr),
               sizeof(server_addr));
    }
}

void load_balancer_client::start_client() {
    create_socket();
    signal(SIGTERM, signal_handler);
    send_datagram();
}
=======
>>>>>>> 809be37 (create class load_balancer_client)
