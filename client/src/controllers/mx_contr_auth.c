#include "header.h"

static void write_data(json_object *obj, t_event *event) {
    event->data = (t_data *)malloc(sizeof(t_data));
    struct json_object *status;
    struct json_object *auth_token;
    struct json_object *tokens;
    struct json_object *id;

    json_object_object_get_ex(obj, "status", &status);
    json_object_object_get_ex(obj, "auth_token", &auth_token);
    json_object_object_get_ex(obj, "tokens", &tokens);
    json_object_object_get_ex(obj, "id", &id);

    event->data->status = json_object_get_int(status);
    event->data->auth_token = json_object_get_string(auth_token);
    event->data->tokens = json_object_get_int(tokens);
    event->data->id = json_object_get_int(id);

    if (event->data->status == 0)
        mx_model_logined(event->data);

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

    write_data(obj, event);
}
