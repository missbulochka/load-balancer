#include <iostream>
#include "load_balancer_server.h"

int main() {
    load_balancer_server server;

    server.start_server();

    return 0;
}
