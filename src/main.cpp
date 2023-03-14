#include "config.h"
#include "load_balancer_client.h"

int main() {
    config conf;
    load_balancer_client client;
    client.start_client();

    return 0;
}
