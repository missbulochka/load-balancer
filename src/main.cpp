#include "config.h"
#include "load_balancer_server.h"
#include "load_balancer_client.h"

int main() {
    config conf;
    load_balancer_server server;
    load_balancer_client client;
    client.start_client();
    server.start_server();

    return 0;
}
