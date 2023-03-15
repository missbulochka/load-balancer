#include <iostream>
#include "load_balancer_server.h"

int main() {
    load_balancer_server server;

    server.recv_datagram();

    return 0;
}
