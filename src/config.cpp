#include "config.h"
#include <fstream>
#include <iostream>

config::config()
    : port(50055)
    , max_number_of_datagrams(10)
    , workers() {
    get_conf();
}

std::pair<std::string, std::uint16_t> config::make_addr_pair(const std::string& some_addr) {
    std::pair<std::string, std::uint16_t> node{};
    auto pos = some_addr.find(':');

    node.first = some_addr.substr(0, pos);
    node.second = std::stoi(some_addr.substr(pos + 1));

    return node;
}

void config::get_conf() {
    std::string config_string{};
    std::fstream config_file("../src/load_balancer.conf");

    if (!config_file.is_open()) {
        std::cout << "Unable to open config file\n";
        return;
    }

    for (config_file >> config_string; !config_file.eof(); config_file >> config_string) {
        if (config_string == "port:") {
            config_file >> port;
        }
        else if (config_string == "max_number_of_datagrams:") {
            int recv_number{};
            config_file >> recv_number;
            if (recv_number < 0) {
                std::cout << "Bad number of datagrams. Max number of datagrams will be = 0\n";
                max_number_of_datagrams = 0;
            } else {
                max_number_of_datagrams = recv_number;
            }
        }
        else if (config_string == "workers:") {
            while (config_file >> config_string) {
                workers.push_back(make_addr_pair(config_string));
            }
        }
    }
}

std::uint16_t config::get_port() const {
    return port;
}

std::uint32_t config::get_max_number_of_datagrams() const {
    return max_number_of_datagrams;
}

std::vector<std::pair<std::string, std::uint16_t>> config::get_workers() const {
    return workers;
}
