#include "balancer.h"
#include <iostream>

balancer::balancer()
    : exit_flag(false)
    , next(0)
    , datagram()
    , balancer_thread(&balancer::balancer_run, this)
    , bucket{conf.get_max_number_of_datagrams(), false, bucket.my_cbs, std::time(nullptr)} {
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
        if ((bucket.my_tcs == 0) && (std::time(nullptr) - bucket.fix_time < 1)) {
            if (!bucket.msg_flag) {
                std::cout << "Datagrams are drop\n";
                bucket.msg_flag = true;
            }
            continue;
        }
        else if (bucket.my_tcs == 0) {
            std::time(&bucket.fix_time);
            bucket.my_tcs = bucket.my_cbs;
            bucket.msg_flag = false;
        }

        if (!(datagram = server.recv_datagram()).empty()) {
            client.send_datagram(get_next_node(), &datagram);
            bucket.my_tcs--;
        }
        else {
            std::cout << "Datagram is not received\n";
        }
    }
}

std::pair<std::string, std::uint16_t> balancer::get_next_node() {
    next = (next + 1) % conf.get_workers().size();

    return conf.get_workers().at(next);
}

void balancer::stop_balancer() {
    std::cout << "Balancer stop to work\n";
    exit_flag = true;
    balancer_thread.join();
    server.stop_server();
    client.stop_client();
}
