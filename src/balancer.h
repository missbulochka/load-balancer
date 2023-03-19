#ifndef LOAD_BALANCER_BALANCER_H
#define LOAD_BALANCER_BALANCER_H

#include "config.h"
#include "load_balancer_server.h"
#include "load_balancer_client.h"

class balancer {
public:
    balancer();

private:
    bool flag;
    std::string datagram;
    config conf;
    load_balancer_server server;
    load_balancer_client client;

    void start_balancer();
    void balancer_work();
    std::pair<std::string, std::uint16_t> get_next_node();
};


#endif  //LOAD_BALANCER_BALANCER_H
