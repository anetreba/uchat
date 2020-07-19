#include "header.h"

void mx_json_read(t_event *event) {
    int n = 0;
    char buf;
    char *str = mx_strnew(0);
    struct json_object *obj = json_object_new_object();

    while ((n = read(event->network_socket, &buf, 1)) > 0) {
        str = mx_parse_str(str, buf);
        if (str[strlen(str) - 1] == '}') {
            break ;
        }
    }
    parse_json((const char *)str, &obj);
    mx_valid_event(obj, event);
}

void mx_valid_event(struct json_object *jobj, t_event *event) {
    struct json_object *obj;
    char *events[] = {"renew_rooms_response", "renew_response", "new_message", "signup_response", "signin_response"};
    const char *ev;

    json_object_object_get_ex(jobj, "event", &obj);
    ev = json_object_get_string(obj);
    if (strcmp(ev, events[0]) == 0)
        mx_contr_update_rooms(jobj);
    if (strcmp(ev, events[1]) == 0)
        mx_contr_renew(event, jobj);
    if (strcmp(ev, events[2]) == 0)
        printf("%s\n", ev);
    if (strcmp(ev, events[3]) == 0)
        printf("%s\n", ev);
    if (strcmp(ev, events[4]) == 0){
        mx_contr_auth(event, jobj);
    }
}
