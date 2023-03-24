#ifndef LOAD_BALANCER_BALANCER_H
#define LOAD_BALANCER_BALANCER_H

#include "config.h"
#include "load_balancer_server.h"
#include "load_balancer_client.h"
#include <thread>
#include <chrono>

struct package_lim {
    std::uint32_t count;
    std::chrono::high_resolution_clock::time_point fixed_time;
};

class balancer {
public:
    balancer();

private:
    bool exit_flag;
    size_t next;
    std::string datagram;
    config conf;
    load_balancer_server server;
    load_balancer_client client;
    std::thread balancer_thread;
    struct package_lim package_limit;

    void start_balancer();
    void balancer_run();
    bool sending_is_available();
    std::pair<std::string, std::uint16_t> get_next_node();
    void stop_balancer();
};


#endif  //LOAD_BALANCER_BALANCER_H
