#ifndef LOAD_BALANCER_CONF_INFORMATION_H
#define LOAD_BALANCER_CONF_INFORMATION_H

#include "iostream"
#include "vector"

class conf_information {
public:
    int read_node{0};
    int max_number_of_datagrams{0};
    std::vector<std::string> available_node{};

    void get_conf();
};


#endif //LOAD_BALANCER_CONF_INFORMATION_H
