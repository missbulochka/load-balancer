#ifndef LOAD_BALANCER_BALANCER_H
#define LOAD_BALANCER_BALANCER_H

#include "config.h"
#include "load_balancer_server.h"
#include "load_balancer_client.h"
#include <thread>

class balancer {
public:
    balancer();

private:
    bool exit_flag;
    std::uint16_t next;
    std::string datagram;
    config conf;
    std::vector<std::pair<std::string, std::uint16_t>> workers;
    load_balancer_server server;
    load_balancer_client client;
    std::thread balancer_thread;

    void start_balancer();
    void balancer_run();
    std::pair<std::string, std::uint16_t> get_next_node();
    void stop_balancer();
};


#endif  //LOAD_BALANCER_BALANCER_H
