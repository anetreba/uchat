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

    printf("#############################################################\n");
    printf("STR = %s\n", str);
    printf("#############################################################\n");
    mx_valid_event(obj, event);
}

void mx_valid_event(struct json_object *jobj, t_event *event) {
    struct json_object *obj;
    char *events[] = {"renew_rooms_response", "renew_resp", "new_message", "signup_response",
                      "signin_response", "add_contact", "renew_contacts", "del_contact", "del_room",
                      "update_room", "update_user"};
    const char *ev;

    json_object_object_get_ex(jobj, "event", &obj);
    ev = json_object_get_string(obj);
    if (strcmp(ev, events[0]) == 0) {
        mx_contr_update_rooms(jobj, event);
        struct json_object *obj = json_object_new_object();
        char *jstr;

        if (event->data) {
            json_object_object_add(obj, "event", json_object_new_string("renew"));
            json_object_object_add(obj, "id", json_object_new_int(event->data->id));
            json_object_object_add(obj, "auth_token", json_object_new_string(event->data->auth_token));
            json_object_object_add(obj, "last_renew", json_object_new_int(0));
            jstr = (char *) json_object_to_json_string(obj);
            send(event->network_socket, jstr, strlen(jstr), 0);
            printf("RENEW_REQ: %s\n", jstr);
            mx_strdel(&jstr);
        }
        mx_json_read(event);
    }
    if (strcmp(ev, events[1]) == 0)
        mx_contr_renew(event, jobj);
    if (strcmp(ev, events[2]) == 0)
        mx_contr_new_message(event, jobj);
    if (strcmp(ev, events[3]) == 0)
        mx_contr_signup(event, jobj);
    if (strcmp(ev, events[4]) == 0){
        mx_contr_auth(event, jobj);
    }
}
