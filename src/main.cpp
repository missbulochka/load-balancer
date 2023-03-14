#include "load_balancer_client.h"
#include "conf_information.h"

int main() {
    config conf;
    load_balancer_client client;
    client.start_client();

    return 0;
}
