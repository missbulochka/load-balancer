#include "load_balancer_server.h"
#include <sys/socket.h>

load_balancer_server::load_balancer_server()
    : sockfd(-1)
    , port(5000)
    , datagram()
    , client_address_len(sizeof(client_addr))
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
    while (true) {
        if (recvfrom(sockfd,
                     reinterpret_cast<void*>(datagram),
                     sizeof(datagram),
                     MSG_WAITALL,
                     reinterpret_cast<struct sockaddr*>(&client_addr),
                     &client_address_len)
            == -1) {
            perror("Error receiving datagram from socket");
            exit(EXIT_FAILURE);
        }
    }
}
