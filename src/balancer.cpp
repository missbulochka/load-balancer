#include "balancer.h"
#include <iostream>

balancer::balancer()
    : exit_flag(false)
    , next(0)
    , datagram()
    , balancer_thread(&balancer::balancer_run, this)
    , lim{0, std::chrono::high_resolution_clock::now()} {
    start_balancer();
}

void balancer::start_balancer() {
    log.open("../src/log.txt");
    log << "Start" << std::endl;
    log.close();
    log.open("../src/log.txt", std::ios::app);

    server.start_server(conf.get_port());
    client.start_client();

    getchar();
    log.close();
    stop_balancer();
}

void balancer::balancer_run() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::cout << "Balancer start to work\n";

    while (!exit_flag) {
        if (!(datagram = server.recv_datagram()).empty()) {
            if (!sending_is_available()) {
                std::cout << "Datagram rejected\n";
                continue;
            }
            if (client.send_datagram(get_next_node(), &datagram)) {
                log << lim.count << ": "
                    << std::chrono::system_clock::to_time_t(std::chrono::high_resolution_clock::now()) << std::endl;
                lim.count++;
            }
        }
        else {
            std::cout << "Datagram is not received\n";
        }
    }
}

bool balancer::sending_is_available() {
    if (conf.get_max_number_of_datagrams() == 0) {
        return false;
    }

    auto current_duration = [this]() {
        auto duration = std::chrono::high_resolution_clock::now() - this->lim.fixed_time;
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    };

    if (current_duration() < 1000) {
        if (lim.count >= conf.get_max_number_of_datagrams()) {
            return false;
        }
        else {
            return true;
        }
    }
    else {
        log << "New start" << std::endl;
        lim.fixed_time = std::chrono::high_resolution_clock::now();
        lim.count = 0;
        return true;
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
