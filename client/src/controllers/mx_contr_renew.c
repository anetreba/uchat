#include "header.h"

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

void mx_contr_renew(json_object *jobj) {
    t_renew *udata = (t_renew *)malloc(sizeof(t_renew));
    memset(udata, 0, sizeof(t_renew));
    t_list *lst = (t_list *)malloc(sizeof(t_list));

    lst =  mx_create_node(udata);
    json_parse(jobj, lst);
    mx_pop_front(&lst);
    if (lst) {
        while (lst) {
            if (mx_check_msgs(lst) != 1) {
                write_data_to_db(jobj);
            }
            lst = lst->next;
        }
    }
}
