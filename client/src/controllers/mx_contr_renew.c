#include "header.h"


void mx_json_read(t_event *event) {
    int n = 0;
    char buf;
    char *str = mx_strnew(0);
    struct json_object *obj = json_object_new_object();

    while ((n = read(event->network_socket, &buf, 1)) > 0) {
        printf("error\n");
        str = mx_parse_str(str, buf);
        printf("BUF = %c\n", buf);
        if (str[strlen(str) - 1] == '}') {
            break ;
        }
    }
    parse_json((const char *)str, &obj);

    printf("JOBJ = %s\n", json_object_to_json_string(obj));
}

void mx_contr_renew(t_event *event, t_data *data) {
    struct json_object *jobj = json_object_new_object();
    json_object_object_add(jobj, "event", json_object_new_string("renew"));
    json_object_object_add(jobj, "id", json_object_new_int(data->id));
    json_object_object_add(jobj, "auth_token", json_object_new_string(data->auth_token));
    json_object_object_add(jobj, "last_renew", json_object_new_int(0));

    printf("obj == %s\n", json_object_to_json_string(jobj));


    char *jstr = (char *)json_object_to_json_string(jobj);
    printf("JSON  == %s\n", jstr);

    send(event->network_socket, jstr, strlen(jstr), 0);
    mx_strdel(&jstr);
    mx_json_read(event);

    //write_data(obj);
}
