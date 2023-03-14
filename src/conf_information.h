#ifndef LOAD_BALANCER_CONF_INFORMATION_H
#define LOAD_BALANCER_CONF_INFORMATION_H

#include <string>
#include <vector>

class conf_information {
public:
    conf_information();

    std::uint32_t get_port() const;

    std::uint32_t get_max_number_of_datagrams() const;

    std::vector<std::string> get_available_node();

private:
    std::uint32_t port{0};
    std::uint32_t max_number_of_datagrams{0};
    std::vector<std::string> available_node{};

    void get_conf();
};


#endif //LOAD_BALANCER_CONF_INFORMATION_H
