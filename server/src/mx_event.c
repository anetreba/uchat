#include "header.h"
//void mx_print_list(t_list *lst) {
//    while(lst) {
//        printf("********************************************************\n");
////        printf("MESSAGE = %s\n",((t_upd *)(lst->data))->message);
//        printf("ROOM ID = %d\n",((t_upd *)(lst->data))->room_id);
//        printf("ROOM NAME = %s\n",((t_upd *)(lst->data))->room_name);
////        printf("SENDER ID = %d\n",((t_upd *)(lst->data))->sender_id);
////        printf("DATA SEND = %d\n",((t_upd *)(lst->data))->date_send);
////        printf("REC STATUS = %d\n",((t_upd *)(lst->data))->recieve_status);
//        lst = lst->next;
//        printf("********************************************************\n");
//    }
//}

void mx_return_renew_rooms_json(t_list *resp, int sock) {
    struct json_object *jobj = json_object_new_object();
    json_object *jarray = NULL;
    char *iter = NULL;
    //mx_print_list(resp);
    json_object_object_add(jobj, "event", json_object_new_string("renew_rooms_response"));
    if (resp) {
        for (int i = 0; resp; i++) {
            jarray = json_object_new_array();
            json_object *jstring0 = json_object_new_int(((t_renew_rooms *)(resp->data))->room_id);
            json_object *jstring1 = json_object_new_string(((t_renew_rooms *)(resp->data))->room_name);
            json_object_array_add(jarray,jstring0);
            json_object_array_add(jarray,jstring1);
            resp = resp->next;
            iter = mx_itoa(i);
            json_object_object_add(jobj, iter, jarray);
        }
    }
    else {
        json_object_object_add(jobj, "status", json_object_new_int(1));
    }

    char *jstr = (char *)json_object_to_json_string(jobj);
    printf("JSON  == %s\n", jstr);
    send(sock, jstr, strlen(jstr), 0);
    mx_strdel(&jstr);
}

void mx_return_renew_json(t_list *resp, int sock) {
    struct json_object *jobj = json_object_new_object();
    json_object *jarray = NULL;
    char *iter = NULL;

    json_object_object_add(jobj, "event", json_object_new_string("renew"));
    if (resp) {
        for (int i = 0; resp; i++) {
            jarray = json_object_new_array();
            json_object *jstring0 = json_object_new_int(((t_upd *)(resp->data))->room_id); // id komnaty
            json_object *jstring1 = json_object_new_string(((t_upd *)(resp->data))->room_name); // imya komnaty
            json_object *jstring2 = json_object_new_string(((t_upd *)(resp->data))->message); // soobschenie
            json_object *jstring3 = json_object_new_int(((t_upd *)(resp->data))->sender_id); // id otpravitelya
            json_object *jstring4 = json_object_new_int(((t_upd *)(resp->data))->date_send); // data otpravki
            json_object *jstring5 = json_object_new_int(((t_upd *)(resp->data))->recieve_status); // status polucheniya
            json_object_array_add(jarray,jstring0);
            json_object_array_add(jarray,jstring1);
            json_object_array_add(jarray,jstring2);
            json_object_array_add(jarray,jstring3);
            json_object_array_add(jarray,jstring4);
            json_object_array_add(jarray,jstring5);
            resp = resp->next;
            iter = mx_itoa(i);
            json_object_object_add(jobj, iter, jarray);
        }
    }
    else {
        json_object_object_add(jobj, "status", json_object_new_int(1));
    }
    char *jstr = (char *)json_object_to_json_string(jobj);
    printf("JSON  == %s\n", jstr);

    send(sock, jstr, strlen(jstr), 0);

    mx_strdel(&jstr);
}

void mx_return_signin_json(t_response *resp, int sock) {
    struct json_object *jobj = json_object_new_object();
    json_object_object_add(jobj, "event", json_object_new_string("signin_response"));
    json_object_object_add(jobj, "id", json_object_new_int(resp->id));
    json_object_object_add(jobj, "status", json_object_new_int(resp->status));
    //printf("obj == %s\n", json_object_to_json_string(jobj));

    if (resp->auth_token)
        json_object_object_add(jobj, "auth_token", json_object_new_string(resp->auth_token));
    json_object_object_add(jobj, "tokens", json_object_new_int(resp->tokens));

    char *jstr = (char *)json_object_to_json_string(jobj);
    printf("JSON  == %s\n", jstr);

    send(sock, jstr, strlen(jstr), 0);
    mx_strdel(&jstr);
}

void mx_return_signup_json(t_signup status, int sock) {
    struct json_object *jobj = json_object_new_object();

    json_object_object_add(jobj, "event", json_object_new_string("signup_response"));
    json_object_object_add(jobj, "status", json_object_new_int(status.status));
    json_object_object_add(jobj, "tokens", json_object_new_int(20));
    json_object_object_add(jobj, "verify_code", json_object_new_int(status.verify_code));

    char *jstr = (char *)json_object_to_json_string(jobj);
    printf("JSON  == %s\n", jstr);

    send(sock, jstr, strlen(jstr), 0);
    mx_strdel(&jstr);
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

void mx_renew_rooms(struct json_object *jobj, t_event *event) {
//    t_event event;
    struct json_object *auth_token;
    t_list *resp;

    event->renew_rooms = (t_renew_rooms *)malloc(sizeof(t_renew_rooms));
    json_object_object_get_ex(jobj, "auth_token", &auth_token);
    event->renew_rooms->auth_token = json_object_get_string(auth_token);
    resp = mx_contr_renew_rooms(event->renew_rooms);
    mx_return_renew_rooms_json(resp, event->new_open_socket);
}

void mx_renew(struct json_object *jobj, t_event *event) {
//    t_event event;
    struct json_object *auth_token;
    t_list *resp;

    event->renew = (t_renew *)malloc(sizeof(t_renew));
    json_object_object_get_ex(jobj, "auth_token", &auth_token);
    event->renew->auth_token = json_object_get_string(auth_token);
    resp = mx_contr_renew(event->renew);
    mx_return_renew_json(resp, event->new_open_socket);
}

void mx_sign_up(struct json_object *jobj, const char *ev, char **events, t_event *event) {
//    t_event event;
    t_data *data;
    struct json_object *nick;
    struct json_object *password;
    struct json_object *login;
    struct json_object *email;

    data = (t_data *) malloc(sizeof(t_data));

    event->log_in = (t_log_in *) malloc(sizeof(t_log_in));
    json_object_object_get_ex(jobj, "login", &login);
    json_object_object_get_ex(jobj, "password", &password);
    json_object_object_get_ex(jobj, "nick", &nick);
    json_object_object_get_ex(jobj, "email", &email);

    event->log_in->login = json_object_get_string(login);
    event->log_in->nick = json_object_get_string(nick);
    event->log_in->password = json_object_get_string(password);
    event->log_in->email = json_object_get_string(email);

    if (strcmp(ev, events[0]) == 0)
        mx_return_signup_json(mx_contr_signup(event->log_in), event->new_open_socket);
}

void mx_sign_in(struct json_object *jobj, const char *ev, char **events, t_event *event) {
//    t_event event;
    t_data *data;
    t_response *resp = NULL;
    struct json_object *password;
    struct json_object *login;

    data = (t_data *)malloc(sizeof(t_data));

    event->log_in = (t_log_in *)malloc(sizeof(t_log_in));
    json_object_object_get_ex(jobj, "login", &login);
    json_object_object_get_ex(jobj, "password", &password);

    event->log_in->login = json_object_get_string(login);
    event->log_in->password = json_object_get_string(password);

    if (strcmp(ev, events[1]) == 0) {
        resp = mx_contr_signin(event->log_in);
        mx_return_signin_json(resp, event->new_open_socket);
    }
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

void mx_valid_event(struct json_object *jobj, t_event *event) {
    struct json_object *action;
    char *events[] = {"sign_up", "sign_in", "renew_rooms", "renew","send_message"};
    const char *ev;

    json_object_object_get_ex(jobj, "event", &action);
    ev = json_object_get_string(action);
    if (strcmp(ev, events[0]) == 0)
        mx_sign_up(jobj, ev, events, event);
    else if (strcmp(ev, events[1]) == 0) {
        mx_sign_in(jobj, ev, events, event);
    }
    else if (strcmp(ev, events[2]) == 0) {
        mx_renew_rooms(jobj, event);
    }
    else if (strcmp(ev, events[3]) == 0) {
        mx_renew(jobj, event);
    }
}
