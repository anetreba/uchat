#include "header.h"

static void write_data_to_db(t_event *event, json_object *obj) {
    event->send_message = (t_send_message *)malloc(sizeof(t_send_message));
    t_list *lst = (t_list *)malloc(sizeof(t_list));

    printf("%s\n", json_object_to_json_string(obj));
    json_parse(obj, lst);



}


void mx_json_read(t_event *event) {
    int n = 0;
    char buf;
    char *str = mx_strnew(0);
    struct json_object *obj = json_object_new_object();

    event->data = (t_data *)malloc(sizeof(t_data));
    memset(event->data, 0, sizeof(t_data));

    while ((n = read(event->network_socket, &buf, 1)) > 0) {
        str = mx_parse_str(str, buf);
        if (str[strlen(str) - 1] == '}') {
            break ;
        }
    }
    parse_json((const char *)str, &obj);
    write_data_to_db(event, obj);
}

void mx_contr_renew(t_event *event) {
    struct json_object *jobj = json_object_new_object();

    if (event->data) {
        json_object_object_add(jobj, "event", json_object_new_string("renew"));
        json_object_object_add(jobj, "id", json_object_new_int(event->data->id));
        json_object_object_add(jobj, "auth_token", json_object_new_string(event->data->auth_token));
        json_object_object_add(jobj, "last_renew", json_object_new_int(0));

        printf("obj == %s\n", json_object_to_json_string(jobj));


        char *jstr = (char *)json_object_to_json_string(jobj);
        printf("JSON  == %s\n", jstr);

        send(event->network_socket, jstr, strlen(jstr), 0);
        mx_strdel(&jstr);
        mx_json_read(event);
    }
    else
        printf("WAT`S WRONG");
}
