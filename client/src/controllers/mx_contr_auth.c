#include "header.h"

static void write_auth_data(t_event *event, json_object *obj) {
    struct json_object *status;
    struct json_object *auth_token;
    struct json_object *tokens;
    struct json_object *id;
    event->data = (t_data *)malloc(sizeof(t_data));
    memset(event->data, 0, sizeof(t_data));

    json_object_object_get_ex(obj, "status", &status);
    json_object_object_get_ex(obj, "auth_token", &auth_token);
    json_object_object_get_ex(obj, "tokens", &tokens);
    json_object_object_get_ex(obj, "id", &id);

    event->data->status = json_object_get_int(status);
    event->data->auth_token = json_object_get_string(auth_token);
    event->data->tokens = json_object_get_int(tokens);
    event->data->id = json_object_get_int(id);

    printf("%d\n",event->data->status);
//    if (event->data->status == 1) {
//        g_print("Wrong login/pass");
//    }
    if(event->data->status == 0) {
        mx_model_logined(event->data);
        mx_contr_renew(event);
    }
}

void mx_contr_auth(t_event *event, json_object *jobj) {
    //char *str = mx_strnew(0);
    struct json_object *obj = json_object_new_object();
    const char *jstr = json_object_to_json_string(jobj);
   // printf("JSON  == %s\n", jstr);
    send(event->network_socket, jstr, strlen(jstr), 0);

    parse_json((const char *)jstr, &obj);
    //printf("JOBJ = %s\n", json_object_to_json_string(obj));

    write_auth_data(event, obj);
}
