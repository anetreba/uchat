#include "header.h"
//void mx_print_list(t_list *lst) {
//    while(lst) {
//        printf("********************************************************\n");
//        printf("MESSAGE = %s\n",((t_upd *)(lst->data))->message);
//        printf("ROOM ID = %d\n",((t_upd *)(lst->data))->room_id);
//        printf("ROOM NAME = %s\n",((t_upd *)(lst->data))->room_name);
//        printf("SENDER ID = %d\n",((t_upd *)(lst->data))->sender_id);
//        printf("DATA SEND = %d\n",((t_upd *)(lst->data))->date_send);
//        printf("REC STATUS = %d\n",((t_upd *)(lst->data))->recieve_status);
//        lst = lst->next;
//        printf("********************************************************\n");
//    }
//}

void mx_return_renew_json(t_list *resp, int sock) {
    struct json_object *jobj = json_object_new_object();
    const char *jstr = NULL;
    json_object *jarray = NULL;


    for (int i = 0; resp; i++) {
        jarray = json_object_new_array();

        json_object *jstring0 = json_object_new_int(((t_upd *)(resp->data))->room_id);
        json_object *jstring1 = json_object_new_string(((t_upd *)(resp->data))->room_name);
        json_object *jstring2 = json_object_new_string(((t_upd *)(resp->data))->message);
        json_object *jstring3 = json_object_new_int(((t_upd *)(resp->data))->sender_id);
        json_object *jstring4 = json_object_new_int(((t_upd *)(resp->data))->date_send);
        json_object *jstring5 = json_object_new_int(((t_upd *)(resp->data))->recieve_status);
        json_object_array_add(jarray,jstring0);
        json_object_array_add(jarray,jstring1);
        json_object_array_add(jarray,jstring2);
        json_object_array_add(jarray,jstring3);
        json_object_array_add(jarray,jstring4);
        json_object_array_add(jarray,jstring5);
        resp = resp->next;
        char *iter = mx_itoa(i);
        json_object_object_add(jobj, iter, jarray);

    }
    jstr = json_object_to_json_string(jobj);
    printf("JSON  == %s\n", jstr);

    send(sock, jstr, strlen(jstr), 0);
}
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

void mx_renew(struct json_object *jobj, int sock) {
    t_event event;
    sock = 0;
    //t_response *resp = NULL;
    struct json_object *auth_token;
    t_list resp;

    event.renew = (t_renew *)malloc(sizeof(t_renew));
    json_object_object_get_ex(jobj, "auth_token", &auth_token);
    event.renew->auth_token = json_object_get_string(auth_token);
    resp = mx_contr_renew(event.renew);
    mx_return_renew_json(&resp, sock);
}

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

//    printf("=====================================================\n");
//    printf("LOGIN = %s\n", event.log_in->login);
//    printf("NICK = %s\n", event.log_in->nick);
//    printf("PASSWORD = %s\n", event.log_in->password);
//    printf("TOKEN = %s\n", resp->auth_token);
//    printf("=====================================================\n");
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
    else if (strcmp(ev, events[2]) == 0)
        mx_renew(jobj, sock);
//    else if (strcmp(ev, events[3]))
//      mx_send_message(jobj, sock);
}
