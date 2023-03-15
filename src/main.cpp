#include "load_balancer_server.h"
#include "config.h"

int main() {
    load_balancer_server server;
    server.start_server();
    config conf;

    return 0;
}
