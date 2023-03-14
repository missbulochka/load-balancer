#include "conf_information.h"
#include <fstream>
#include <iostream>


void get_parameter(std::fstream &config_file, conf_information *this_ptr) {
    std::string config_string{};

    for(config_file >> config_string; !config_file.eof(); config_file >> config_string) {
        if (config_string == "read_node") {
            config_file >> config_string;
            config_file >> this_ptr->read_node;
        } else if (config_string == "max_number_of_datagrams") {
            config_file >> config_string;
            config_file >> this_ptr->max_number_of_datagrams;
        } else {
            config_file >> config_string;
            config_file >> config_string;

            this_ptr->available_node.push_back(config_string);
        }
    }
}


void conf_information::get_conf() {
    std::fstream config_file("../src/load_balancer.conf");

    if (config_file.is_open()) {
        get_parameter(config_file, this);
    } else {
        std::cout << "Unable to open config file\n";
    }

    for (size_t i = {0}; i < available_node.size(); i++) {
        std::cout << available_node[i] << '\n';
    }

    config_file.close();
}
