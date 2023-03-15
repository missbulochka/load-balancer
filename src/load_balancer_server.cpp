#include "load_balancer_server.h"
#include <iostream>
#include <sys/socket.h>
#include <memory>

load_balancer_server::load_balancer_server()
    : sockfd(-1)
    , port(5000)
    , server_response(reinterpret_cast<const std::string*>("Message delivered successfully"))
    , client_response()
    , client_addr{}
    , server_addr{AF_INET, htons(port), INADDR_ANY} {
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (bind(sockfd, reinterpret_cast<const struct sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
}

void load_balancer_server::recv_datagram() {
    std::string datagram{};
    ssize_t datagram_size{0};
    socklen_t client_address_len = sizeof(client_addr);

    while (true) {
        datagram_size = recvfrom(sockfd,
                                 reinterpret_cast<void*>(client_response),
                                 sizeof(client_response),
                                 MSG_WAITALL,
                                 reinterpret_cast<struct sockaddr*>(&client_addr),
                                 &client_address_len);

        client_response[datagram_size] = '\0';
        std::cout << client_response << '\n';
        sendto(sockfd,
               reinterpret_cast<const void*>(server_response),
               server_response->size(),
               MSG_CONFIRM,
               reinterpret_cast<const struct sockaddr*>(&client_addr),
               client_address_len);
        std::cout << "Hello message sent." << std::endl;
    }
}
