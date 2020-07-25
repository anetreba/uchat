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

void mx_return_renew_rooms_json(t_list *resp, int sock) {
    struct json_object *jobj = json_object_new_object();
    json_object *jarray = NULL;
    char *iter = NULL;
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
    json_object_object_add(jobj, "event", json_object_new_string("renew_resp"));
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
    send(sock, jstr, strlen(jstr), 0);
    mx_strdel(&jstr);
}

void mx_return_renew_contacts_json(t_list *resp, int sock) {
    struct json_object *jobj = json_object_new_object();
    json_object *jarray = NULL;
    char *iter = NULL;
    json_object_object_add(jobj, "event", json_object_new_string("renew_contacts_resp"));
    if (resp) {
        for (int i = 0; resp; i++) {
            jarray = json_object_new_array();
            json_object *jstring0 = json_object_new_int(((t_renew_contacts *)(resp->data))->contact_id); // id komnaty
            json_object *jstring1 = json_object_new_string(((t_renew_contacts *)(resp->data))->nickname); // imya komnaty
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
    printf("=============================JSON  == %s================================\n", jstr);
    printf("SOCK = %d\n", sock);
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
    printf("=========================ERROR=========================\n");
    struct json_object *auth_token;
    t_list *resp;

    event->renew_rooms = (t_renew_rooms *)malloc(sizeof(t_renew_rooms));
    json_object_object_get_ex(jobj, "auth_token", &auth_token);
    event->renew_rooms->auth_token = json_object_get_string(auth_token);
    resp = mx_contr_renew_rooms(event->renew_rooms);
    mx_return_renew_rooms_json(resp, event->new_open_socket);
}

void mx_renew(struct json_object *jobj, t_event *event) {
    struct json_object *auth_token;
    t_list *resp;
    printf("=========================ERROR1=========================\n");

    event->renew = (t_renew *)malloc(sizeof(t_renew));
    json_object_object_get_ex(jobj, "auth_token", &auth_token);
    event->renew->auth_token = json_object_get_string(auth_token);
    resp = mx_contr_renew(event->renew);
    mx_return_renew_json(resp, event->new_open_socket);
}

void mx_renew_contacts(json_object *jobj, t_event *event) {
    struct json_object *auth_token;
    t_list *resp;
    printf("=========================ERROR5=========================\n");

    event->renew_contacts = (t_renew_contacts *)malloc(sizeof(t_renew_contacts));
    json_object_object_get_ex(jobj, "auth_token", &auth_token);
    event->renew_contacts->auth_token = json_object_get_string(auth_token);
    resp = mx_contr_renew_contacts(event->renew_contacts);
    mx_return_renew_contacts_json(resp, event->new_open_socket);
}

void mx_send_message(struct json_object *jobj, t_event *event) {
    struct json_object *auth_token;
    struct json_object *message;
    struct json_object *room_id;
    struct json_object *sender_id;

    t_list *resp;
    printf("=========================ERROR2=========================\n");

    event->send_message = (t_send_message *)malloc(sizeof(t_send_message));
    json_object_object_get_ex(jobj, "auth_token", &auth_token);
    json_object_object_get_ex(jobj, "message", &message);
    json_object_object_get_ex(jobj, "room_id", &room_id);
    json_object_object_get_ex(jobj, "sender_id", &sender_id);
    event->send_message->auth_token = json_object_get_string(auth_token);
    event->send_message->message = json_object_get_string(message);
    event->send_message->room_id = json_object_get_int(room_id);
    event->send_message->sender_id =json_object_get_int(sender_id);

    resp = mx_recieve_mess(event->send_message);
    //mx_return_sendmessage_json(resp, event->new_open_socket);
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
        resp = mx_contr_signin(event);
        mx_return_signin_json(resp, event->new_open_socket);
    }
}

//void mx_edit_room(struct json_object *jobj, const char *ev, char **events, t_event *event) {
//    t_data *data;
//    t_response *resp = NULL;
//    struct json_object *id;
//    struct json_object *room_name;
//
//    data = (t_data *)malloc(sizeof(t_data));
//
//    event->log_in = (t_log_in *)malloc(sizeof(t_log_in));
//    json_object_object_get_ex(jobj, "login", &login);
//    json_object_object_get_ex(jobj, "password", &password);
//
//    event->log_in->login = json_object_get_string(login);
//    event->log_in->password = json_object_get_string(password);
//
//    if (strcmp(ev, events[1]) == 0) {
//        resp = mx_contr_signin(event);
//        mx_return_signin_json(resp, event->new_open_socket);
//    }
//}

//void mx_add_group(struct json_object *jobj, const char *ev, char **events, t_event *event) {
//    t_data *data;
//    t_response *resp = NULL;
//    struct json_object *id;
//
//    data = (t_data *)malloc(sizeof(t_data));
//
//    event->log_in = (t_log_in *)malloc(sizeof(t_log_in));
//    json_object_object_get_ex(jobj, "login", &login);
//    json_object_object_get_ex(jobj, "password", &password);
//
//    event->log_in->login = json_object_get_string(login);
//    event->log_in->password = json_object_get_string(password);
//
//    if (strcmp(ev, events[1]) == 0) {
//        resp = mx_contr_signin(event);
//        mx_return_signin_json(resp, event->new_open_socket);
//    }
//}

void mx_return_del_room_json(t_event *ev, int sock) {
    struct json_object *jobj = json_object_new_object();
    json_object_object_add(jobj, "event", json_object_new_string("del_room_response"));
    json_object_object_add(jobj, "room_id", json_object_new_int(ev->edit_room->room_id));

    char *jstr = (char *)json_object_to_json_string(jobj);
    printf("JSON  == %s\n", jstr);

    send(sock, jstr, strlen(jstr), 0);
    mx_strdel(&jstr);
}

void mx_del_room(struct json_object *jobj, t_event *event) {
    struct json_object *room_id;
    struct json_object *user_id;
    struct json_object *auth_token;

    event->edit_room = (t_edit_room *)malloc(sizeof(t_edit_room));
    json_object_object_get_ex(jobj, "room_id", &room_id);
    json_object_object_get_ex(jobj, "user_id", &user_id);
    json_object_object_get_ex(jobj, "auth_token", &auth_token);

    event->edit_room->room_id = json_object_get_int(room_id);
    event->edit_room->user_id = json_object_get_int(user_id);
    event->edit_room->auth_token = json_object_get_string(auth_token);
    mx_contr_del_room(event->edit_room);
    mx_return_del_room_json(event, event->new_open_socket);
}

void mx_return_add_contact_json(int resp, t_event *event) {
    struct json_object *jobj = json_object_new_object();
    json_object_object_add(jobj, "event", json_object_new_string("add_contact_response"));
    json_object_object_add(jobj, "contact_id", json_object_new_int(resp));
    json_object_object_add(jobj, "nick", json_object_new_string(event->add_contact->nick));

    char *jstr = (char *)json_object_to_json_string(jobj);
    printf("JSON  == %s\n", jstr);

    send(event->new_open_socket, jstr, strlen(jstr), 0);
    mx_strdel(&jstr);
}

void mx_add_contact(struct json_object *jobj, t_event *event) {
    int resp;
    struct json_object *nick;
    struct json_object *sender_id;
    struct json_object *auth_token;

    event->add_contact = (t_add_contact *)malloc(sizeof(t_add_contact));
    json_object_object_get_ex(jobj, "nick", &nick);
    json_object_object_get_ex(jobj, "sender_id", &sender_id);
    json_object_object_get_ex(jobj, "auth_token", &auth_token);
    event->add_contact->nick = json_object_get_string(nick);
    event->add_contact->sender_id = json_object_get_int(sender_id);
    event->add_contact->auth_token = json_object_get_string(auth_token);
    resp = mx_contr_add_contact(event->add_contact);
    mx_return_add_contact_json(resp, event);
}

void mx_valid_event(struct json_object *jobj, t_event *event) {
    struct json_object *action;
    char *events[] = {"sign_up", "sign_in", "renew_rooms", "renew","send_message",
                      "renew_contacts", "add_room", "edit_room", "del_room",
                      "add_contact", "del_contact"};
    const char *ev;

    json_object_object_get_ex(jobj, "event", &action);
    ev = json_object_get_string(action);
    if (strcmp(ev, events[0]) == 0)
        mx_sign_up(jobj, ev, events, event);
    else if (strcmp(ev, events[1]) == 0)
        mx_sign_in(jobj, ev, events, event);
    else if (strcmp(ev, events[2]) == 0)
        mx_renew_rooms(jobj, event);
    else if (strcmp(ev, events[3]) == 0)
        mx_renew(jobj, event);
    else if (strcmp(ev, events[4]) == 0)
        mx_send_message(jobj, event);
    else if (strcmp(ev, events[5]) == 0)
        mx_renew_contacts(jobj, event);
//    else if (strcmp(ev, events[6]) == 0)
//        mx_add_room(jobj, event);
//    else if (strcmp(ev, events[7]) == 0)
//        mx_edit_room(jobj, event);
    else if (strcmp(ev, events[8]) == 0)
        mx_del_room(jobj, event);
    else if (strcmp(ev, events[9]) == 0)
        mx_add_contact(jobj, event);
//    const char *jstr = json_object_to_json_string(jobj);
//    printf("JSON  == %s\n", jstr);
}
