#include "header.h"

void *mx_client_recv(void *data) {
    t_event *event = (t_event *)data;

    mx_json_read(event);

    return NULL;
}
