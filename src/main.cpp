#include "config.h"
#include "load_balancer_server.h"

int main() {
    config conf;
    load_balancer_server server;
    server.start_server();

    return 0;
}
