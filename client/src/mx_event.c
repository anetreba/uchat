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

//void mx_return_renew_rooms_json(t_list *resp, int sock) {
//    struct json_object *jobj = json_object_new_object();
//    json_object *jarray = NULL;
//    char *iter = NULL;
//    if (resp){
//        json_object_object_add(jobj, "event", json_object_new_string("renew_rooms"));
//        for (int i = 0; resp; i++) {
//            jarray = json_object_new_array();
//            json_object *jstring0 = json_object_new_int(((t_renrooms *)(resp->data))->room_id);
//            json_object *jstring1 = json_object_new_string(((t_renrooms *)(resp->data))->room_name);
//            json_object_array_add(jarray,jstring0);
//            json_object_array_add(jarray,jstring1);
//            resp = resp->next;
//            iter = mx_itoa(i);
//            json_object_object_add(jobj, iter, jarray);
//        }
//    }
//    char *jstr = (char *)json_object_to_json_string(jobj);
//    printf("JSON  == %s\n", jstr);
//    send(sock, jstr, strlen(jstr), 0);
//    mx_strdel(&jstr);
//}
//
//void mx_return_renew_json(t_list *resp, int sock) {
//    struct json_object *jobj = json_object_new_object();
//    //const char *jstr = NULL;
//    json_object *jarray = NULL;
//    char *iter = NULL;
//
//    if (resp) {
//        for (int i = 0; resp; i++) {
//            jarray = json_object_new_array();
//            json_object *jstring0 = json_object_new_int(((t_upd *)(resp->data))->room_id); // id komnaty
//            json_object *jstring1 = json_object_new_string(((t_upd *)(resp->data))->room_name); // imya komnaty
//            json_object *jstring2 = json_object_new_string(((t_upd *)(resp->data))->message); // soobschenie
//            json_object *jstring3 = json_object_new_int(((t_upd *)(resp->data))->sender_id); // id otpravitelya
//            json_object *jstring4 = json_object_new_int(((t_upd *)(resp->data))->date_send); // data otpravki
//            json_object *jstring5 = json_object_new_int(((t_upd *)(resp->data))->recieve_status); // status polucheniya
//            json_object_array_add(jarray,jstring0);
//            json_object_array_add(jarray,jstring1);
//            json_object_array_add(jarray,jstring2);
//            json_object_array_add(jarray,jstring3);
//            json_object_array_add(jarray,jstring4);
//            json_object_array_add(jarray,jstring5);
//            resp = resp->next;
//            iter = mx_itoa(i);
//            json_object_object_add(jobj, iter, jarray);
//        }
//    }
//    char *jstr = (char *)json_object_to_json_string(jobj);
//    printf("JSON  == %s\n", jstr);
//
//    send(sock, jstr, strlen(jstr), 0);
//
//    mx_strdel(&jstr);
//}

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
    mx_valid_event(obj, event);
}

void mx_valid_event(struct json_object *jobj, t_event *event) {
    struct json_object *obj;
    char *events[] = {"renew_rooms", "new_message", "signup_response", "signin_response"};
    const char *ev;

    json_object_object_get_ex(jobj, "event", &obj);
    ev = json_object_get_string(obj);
    if (strcmp(ev, events[0]) == 0){
        printf("%s\n", ev);
    }
//        mx_update_rooms(jobj, ev, events, sock);
    if (strcmp(ev, events[1]) == 0)
        printf("%s\n", ev);
//        mx_new_message(jobj, ev, events, sock);
    if (strcmp(ev, events[2]) == 0)
        printf("signup_response\n");
    if (strcmp(ev, events[3]) == 0){
        mx_contr_auth(event, jobj);
    }
}
