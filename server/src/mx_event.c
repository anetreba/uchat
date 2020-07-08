#include "header.h"
void mx_return_signin_json(t_response resp, int sock) {
    struct json_object *jobj = json_object_new_object();

    json_object_object_add(jobj, "status", json_object_new_int(resp.status));
    //printf("obj == %s\n", json_object_to_json_string(jobj));

    json_object_object_add(jobj, "auth_token", json_object_new_string(resp.auth_token));
    printf("obj == %s\n", json_object_to_json_string(jobj));

    const char *jstr = json_object_to_json_string(jobj);
    printf("JSON  == %s\n", jstr);

    send(sock, jstr, strlen(jstr), 0);
}

void mx_return_signup_json(int status, int sock) {
    struct json_object *jobj = json_object_new_object();

    json_object_object_add(jobj, "status", json_object_new_int(status));
    printf("obj == %s\n", json_object_to_json_string(jobj));

    json_object_object_add(jobj, "tokens", json_object_new_int(10));
    printf("obj == %s\n", json_object_to_json_string(jobj));

    const char *jstr = json_object_to_json_string(jobj);
    printf("JSON  == %s\n", jstr);

    send(sock, jstr, strlen(jstr), 0);
}

//void mx_return_status_json(int status, int sock) {
//    struct json_object *jobj = json_object_new_object();
//
//    json_object_object_add(jobj, "status", json_object_new_int(status));
//    printf("obj == %s\n", json_object_to_json_string(jobj));
//
//    const char *jstr = json_object_to_json_string(jobj);
//    printf("JSON  == %s\n", jstr);
//
//    send(sock, jstr, strlen(jstr), 0);
//}

void mx_sign_up_in(struct json_object *jobj, const char *ev, char **events, int sock) {
    t_event event;
    t_data *data;
    t_response *resp = NULL;
    struct json_object *nick;
    struct json_object *password;
    struct json_object *login;

    data = (t_data *)malloc(sizeof(t_data));
    event.log_in = (t_log_in *)malloc(sizeof(t_log_in));
    json_object_object_get_ex(jobj, "login", &login);
    json_object_object_get_ex(jobj, "password", &password);
    json_object_object_get_ex(jobj, "nick", &nick);

    event.log_in->login = json_object_get_string(login);
    event.log_in->nick = json_object_get_string(nick);
    event.log_in->password = json_object_get_string(password);

    if (strcmp(ev, events[0]) == 0)
        mx_return_signup_json(mx_contr_signup(event.log_in), sock);
    if (strcmp(ev, events[1]) == 0) {
        resp = mx_contr_signin(event.log_in);
        mx_return_signin_json(*resp, sock);
    }

    printf("=====================================================\n");
    printf("LOGIN = %s\n", event.log_in->login);
    printf("NICK = %s\n", event.log_in->nick);
    printf("PASSWORD = %s\n", event.log_in->password);
    printf("TOKEN = %s\n", resp->auth_token);
    printf("=====================================================\n");
    //int status = 1;
    //mx_return_status_json(status, sock);
}

//void mx_send_message(struct json_object *jobj, int sock) {
//    t_event event;
//    struct json_object *id_sender;
//    struct json_object *message;
//    struct json_object *type;
//    struct json_object *group;
//
//    event.send_message = (t_send_message *)malloc(sizeof(t_send_message));
//    json_object_object_get_ex(jobj, "id_sender", &id_sender);
//    json_object_object_get_ex(jobj, "message", &message);
//    json_object_object_get_ex(jobj, "type", &type);
//    json_object_object_get_ex(jobj, "group", &group);
//
//    event.send_message->message = json_object_get_string(message);
//    event.send_message->id_sender =  json_object_get_int(id_sender);
//    event.send_message->type =  json_object_get_int(type);
//    event.send_message->group =  json_object_get_int(group);
//
//    printf("*****************************************************\n");
//    printf("ID_SENDER = %d\n", event.send_message->id_sender);
//    printf("MESSAGE = %s\n", event.send_message->message);
//    printf("TYPE = %d\n", event.send_message->type);
//    printf("GROUP = %d\n", event.send_message->group);
//    printf("*****************************************************\n");
//
//    int status = 1;
//    mx_return_status_json(status, sock);
//}

void mx_valid_event(struct json_object *jobj, int sock) {
    struct json_object *event;
    char *events[] = {"sign_up", "sign_in", "renew", "send_message"};
    const char *ev;

    json_object_object_get_ex(jobj, "event", &event);
    ev = json_object_get_string(event);
    if ((strcmp(ev, events[0]) == 0) || (strcmp(ev, events[1]) == 0))
        mx_sign_up_in(jobj, ev, events, sock);
//    else if (strcmp(ev, events[2]))
//      mx_send_message(jobj, sock);
}
