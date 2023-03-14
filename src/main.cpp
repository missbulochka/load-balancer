#include "load_balancer_client.h"
#include "conf_information.h"

int main() {
    conf_information conf;
    conf.get_conf();
    load_balancer_client client;
    client.start_client();

    return 0;
}
