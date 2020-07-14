#include "header.h"

static void write_auth_data(t_event *event, json_object *obj) {
    t_data data;
    struct json_object *status;
    struct json_object *auth_token;
    struct json_object *tokens;
    struct json_object *id;

    json_object_object_get_ex(obj, "status", &status);
    json_object_object_get_ex(obj, "auth_token", &auth_token);
    json_object_object_get_ex(obj, "tokens", &tokens);
    json_object_object_get_ex(obj, "id", &id);

    data.status = json_object_get_int(status);
    data.auth_token = json_object_get_string(auth_token);
    data.tokens = json_object_get_int(tokens);
    data.id = json_object_get_int(id);

    if (data.status == 1)
        g_print("Wrong login/pass");
    else if(data.status == 0)
        mx_model_logined(&data);
    mx_contr_renew(event, &data);
}

void mx_contr_auth(t_event *event, json_object *jobj) {
    int n;
    char buf;
    char *str = mx_strnew(0);
    struct json_object *obj = json_object_new_object();
    const char *jstr = json_object_to_json_string(jobj);

    printf("JSON  == %s\n", jstr);
    send(event->network_socket, jstr, strlen(jstr), 0);


    while ((n = read(event->network_socket, &buf, 1)) > 0) {
        str = mx_parse_str(str, buf);
        if (str[strlen(str) - 1] == '}')
            break ;
    }
    parse_json((const char *)str, &obj);
    printf("JOBJ = %s\n", json_object_to_json_string(obj));

    write_auth_data(event, obj);
}
