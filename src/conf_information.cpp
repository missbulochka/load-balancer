#include "conf_information.h"
#include <fstream>
#include <iostream>


conf_information::conf_information() {
    get_conf();
}

void conf_information::get_conf() {
    std::string config_string{};
    std::fstream config_file("../src/load_balancer.conf");

    if (config_file.is_open()) {
        for (config_file >> config_string; !config_file.eof(); config_file >> config_string) {
            if (config_string == "read_node:") {
                config_file >> port;
            } else if (config_string == "max_number_of_datagrams:") {
                config_file >> max_number_of_datagrams;
            } else if (config_string == "workers:") {
                while ((config_file >> config_string) && !config_file.eof()) {
                    available_node.push_back(config_string);
                }
            }
        }
    } else {
        std::cout << "Unable to open config file\n";
    }
}

std::uint32_t conf_information::get_port() const {
    return port;
}

std::uint32_t conf_information::get_max_number_of_datagrams() const {
    return max_number_of_datagrams;
}

std::vector<std::string> conf_information::get_available_node() {
    return available_node;
}
