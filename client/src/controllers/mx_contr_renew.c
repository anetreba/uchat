#include "header.h"

//void mx_print_list(t_list *lst) {
//    while(lst) {
//        printf("********************************************************\n");
//        printf("MESSAGE = %s\n",((t_renew *)(lst->data))->message);
//        printf("ROOM ID = %d\n",((t_renew *)(lst->data))->room_id);
//        printf("ROOM NAME = %s\n",((t_renew *)(lst->data))->name_room);
//        printf("SENDER ID = %d\n",((t_renew *)(lst->data))->sender_id);
//        printf("DATA SEND = %d\n",((t_renew *)(lst->data))->date_send);
//        printf("REC STATUS = %d\n",((t_renew *)(lst->data))->recieve_status);
//        lst = lst->next;
//        printf("********************************************************\n");
//    }
//}
static int callback_check_msg(void *data, int argc, char **argv, char **ColName) {
    ColName = NULL;

    if (argv[0]) {
        argc = 0;
        data = NULL;
        return 1;
    }
    return 0;
}

static int mx_check_msgs(t_list *lst) {
    char *vals;
    int rs;

    asprintf(&vals, "Messages WHERE room_id = '%d' AND message = '%s' AND sender_id = '%d' AND date_send = '%d'",
             ((t_renew *)(lst->data))->room_id,
             ((t_renew *)(lst->data))->message,
             ((t_renew *)(lst->data))->sender_id,
             ((t_renew *)(lst->data))->date_send);
    rs = mx_model_select("id", vals, callback_check_msg, NULL);
    return rs;
}

static void write_data_to_db(json_object *obj) {
    t_renew *udata = (t_renew *)malloc(sizeof(t_renew));
    memset(udata, 0, sizeof(t_renew));
    t_list *lst = (t_list *)malloc(sizeof(t_list));
    lst =  mx_create_node(udata);
    char *vals;

    json_parse(obj, lst);
    mx_pop_front(&lst);
    if (lst){
        while (lst) {
            if (mx_check_msgs(lst) != 1) {
                asprintf(&vals, "'%d','%s','%d','%d','%d'",
                         ((t_renew *)(lst->data))->room_id,
                         ((t_renew *)(lst->data))->message,
                         ((t_renew *)(lst->data))->sender_id,
                         ((t_renew *)(lst->data))->date_send,
                         ((t_renew *)(lst->data))->recieve_status);
                mx_model_insert("Messages", "room_id, message, sender_id, date_send, resieve_status", vals);
            }
            lst = lst->next;
        }
    }
}


static void mx_json_renew(json_object *obj) {
    char *str = (char *)json_object_to_json_string(obj);

    parse_json((const char *)str, &obj);
    write_data_to_db(obj);
}

void mx_contr_renew(t_event *event, json_object *jobj) {
    struct json_object *obj = json_object_new_object();
    char *jstr;

    if (event->data) {
        json_object_object_add(jobj, "event", json_object_new_string("renew"));
        json_object_object_add(jobj, "id", json_object_new_int(event->data->id));
        json_object_object_add(jobj, "auth_token", json_object_new_string(event->data->auth_token));
        json_object_object_add(jobj, "last_renew", json_object_new_int(0));
        jstr = (char *)json_object_to_json_string(obj);
        send(event->network_socket, jstr, strlen(jstr), 0);
        mx_strdel(&jstr);
        mx_json_renew(obj);
    }
    else
        printf("WAT`S WRONG");
}
