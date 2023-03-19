#include "balancer.h"
#include <thread>
#include <iostream>

balancer::balancer()
    : flag(true)
    , datagram() {
    start_balancer();
}

void balancer::start_balancer() {
    server.start_server(conf.get_port());
    client.start_client();

    std::thread balancer_thread(&balancer::balancer_work, this);

    getchar();
    flag = false;

    balancer_thread.join();
}

void balancer::balancer_work() {
    while (flag) {
        if (!(datagram = server.recv_datagram()).empty()) {
            client.send_datagram(std::make_pair("127.55.6.1", 5001), &datagram);
        } else {
            std::cout << "Datagram is not received\n";
        }
    }
}

std::pair<std::string, std::uint16_t> balancer::get_next_node() {
    auto a = std::make_pair("127.0.0.1", 5001);
    return a;
}
