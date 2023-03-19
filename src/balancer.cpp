#include "balancer.h"
#include <iostream>

balancer::balancer()
    : exit_flag(false)
    , next(0)
    , datagram()
    , workers(conf.get_workers())
    , balancer_thread(&balancer::balancer_run, this) {
    start_balancer();
}

void balancer::start_balancer() {
    server.start_server(conf.get_port());
    client.start_client();

    getchar();
    stop_balancer();
}

void balancer::balancer_run() {
    std::cout << "Balancer start to work\n";
    while (!exit_flag) {
        if (!(datagram = server.recv_datagram()).empty()) {
            client.send_datagram(get_next_node(), &datagram);
        }
        else {
            std::cout << "Datagram is not received\n";
        }
    }
}

std::pair<std::string, std::uint16_t> balancer::get_next_node() {
    next = (next + 1) % workers.size();

    return workers[next];
}

void balancer::stop_balancer() {
    std::cout << "Balancer stop to work\n";
    exit_flag = true;
    balancer_thread.join();
    server.stop_server();
    client.stop_client();
}
