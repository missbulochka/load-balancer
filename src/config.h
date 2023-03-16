#ifndef LOAD_BALANCER_CONF_INFORMATION_H
#define LOAD_BALANCER_CONF_INFORMATION_H

#include <string>
#include <vector>

class config {
public:
    config();

    std::uint16_t get_port() const;

    std::uint32_t get_max_number_of_datagrams() const;

    std::vector<std::pair<std::string, std::uint16_t>> get_nodes() const;

private:
    std::uint16_t port;
    std::uint32_t max_number_of_datagrams;
    std::vector<std::pair<std::string, std::uint16_t>> nodes;

    static std::pair<std::string, std::uint16_t> make_addr_pair(const std::string&);
    void get_conf();
};


#endif  //LOAD_BALANCER_CONF_INFORMATION_H
