#include "config.h"
#include <fstream>
#include <iostream>

config::config()
    : port(50055)
    , max_number_of_datagrams(10)
    , available_node() {
    get_conf();
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
            config_file >> max_number_of_datagrams;
        }
        else if (config_string == "workers:") {
            while (config_file >> config_string) {
                available_node.push_back(config_string);
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

std::vector<std::string> config::get_available_node() const {
    return available_node;
}
