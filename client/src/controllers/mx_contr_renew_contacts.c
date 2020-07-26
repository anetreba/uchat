#include "header.h"

void mx_contr_renew_contacts(t_event *event) {
    struct json_object *obj = json_object_new_object();
    char *jstr;

    if (event->data) {
        json_object_object_add(obj, "event", json_object_new_string("renew_contacts"));
        json_object_object_add(obj, "id", json_object_new_int(event->data->id));
        json_object_object_add(obj, "auth_token", json_object_new_string(event->data->auth_token));
        jstr = (char *) json_object_to_json_string(obj);
        send(event->network_socket, jstr, strlen(jstr), 0);
        mx_strdel(&jstr);
    }
    mx_json_read(event);
}
