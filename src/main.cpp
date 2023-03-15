#include "load_balancer_client.h"
#include "config.h"

int main() {
    config conf;
    load_balancer_client client;
    client.start_client();

    return 0;
}
