#ifndef LOAD_BALANCER_BALANCER_H
#define LOAD_BALANCER_BALANCER_H

#include "config.h"
#include "load_balancer_server.h"
#include "load_balancer_client.h"
#include <thread>
#include <ctime>

struct t_bucket {
    const std::uint32_t my_cbs;
    std::uint32_t my_tcs;
    time_t fix_time;
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
    struct t_bucket bucket;

    void start_balancer();
    void balancer_run();
    std::pair<std::string, std::uint16_t> get_next_node();
    void stop_balancer();
};


#endif  //LOAD_BALANCER_BALANCER_H
