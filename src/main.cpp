#include "load_balancer_server.h"
#include "conf_information.h"

int main() {
    load_balancer_server server;
    server.start_server();
    conf_information conf;

    return 0;
}
