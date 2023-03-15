#include "load_balancer_server.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory>


load_balancer_server::load_balancer_server() = default;

void load_balancer_server::recv_datagram() {
    int sockfd{0};
    std::uint16_t port{5000};
    const auto* server_response = reinterpret_cast<const std::string*>("Message delivered successfully");
    std::string client_response[1024];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in client_addr {};

    struct sockaddr_in server_addr {
        AF_INET, htons(port), INADDR_ANY,
    };

    if (bind(sockfd, reinterpret_cast<const struct sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    std::string datagram{};
    ssize_t datagram_size{0};
    socklen_t client_address_len = sizeof(client_addr);

    while (true) {
        datagram_size = recvfrom(sockfd,
                                 reinterpret_cast<std::string*>(client_response),
                                 client_response->size(),
                                 MSG_WAITALL,
                                 reinterpret_cast<struct sockaddr*>(&client_addr),
                                 &client_address_len);

        std::cout << client_response << '\n';
        sendto(sockfd,
               reinterpret_cast<const char*>(server_response),
               server_response->size(),
               MSG_CONFIRM,
               reinterpret_cast<const struct sockaddr*>(&client_addr),
               client_address_len);
        std::cout<<"Hello message sent."<<std::endl;
    }

}
