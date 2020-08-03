#include <header.h>
#include "header.h"

static int callback_sock(void *data, int argc, char **argv, char **ColName) {
    t_list *udata = (t_list *)data;
    ColName = NULL;


    if (argc > 0 && argv[0]) {
//        printf("*****************************************************\n");
        t_sock *sock = (t_sock *)malloc(sizeof(t_sock));
        sock->sock = atoi(argv[0]);
        mx_push_back(&udata, sock);
    }
    printf("=========================%s==============\n", argv[0]);
    return 0;
}

void mx_select_user(t_event *event) {
    char *vals;

    t_sock *sock = (t_sock *)malloc(sizeof(t_sock));
    sock->sock = 0;

    event->sock = mx_create_node(sock);


    for (int i = 0; event->add_room->cont_id[i]; i++) {
        asprintf(&vals, "Users WHERE id = '%d'", event->add_room->cont_id[i]);
        mx_model_select("sock", vals, callback_sock, event->sock);
//        printf("*****************************************************\n");
    }
    mx_pop_front(&(event->sock));

    t_list *lst = event->sock;


    while (lst) {
        printf("%d\n", ((t_sock *)(lst->data))->sock);
        lst = lst->next;
    }
    printf("====================================================\n");
}


void mx_add_room(struct json_object *jobj, t_event *event) {
    struct json_object *room_name;
    struct json_object *sender_id;
    struct json_object *auth_token;
    json_object * jvalue;

    event->add_room = (t_info_room *)malloc(sizeof(t_info_room));

    json_object_object_get_ex(jobj, "room_name", &room_name);
    json_object_object_get_ex(jobj, "sender_id", &sender_id);
    json_object_object_get_ex(jobj, "auth_token", &auth_token);
    event->add_room->room_name = (char *)json_object_get_string(room_name);
    event->add_room->sender_id = json_object_get_int(sender_id);
    event->add_room->auth_token = (char *)json_object_get_string(auth_token);


    json_object *jarray = json_object_object_get(jobj, "users");

    int arraylen = json_object_array_length(jarray);

    event->add_room->users_count = arraylen;
    event->add_room->cont_id = (int *)malloc(sizeof(int) * arraylen);
    int i = 0;

    for ( ; i < arraylen; i++) {
        jvalue = json_object_array_get_idx(jarray, i);
        event->add_room->cont_id[i] = json_object_get_int(jvalue);
    }

    event->add_room->cont_id[i] = 0;
    mx_select_user(event);
printf("555554356345634563456345634563456\n");
    mx_contr_add_new_room(event);

//    t_sock *sock = (t_sock *)malloc(sizeof(t_sock));
//    sock->sock = 0;
//
//    event->sock = mx_create_node(sock);

    mx_add_room_resp(event);
}

