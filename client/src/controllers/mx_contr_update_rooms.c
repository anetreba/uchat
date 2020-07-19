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

    asprintf(&vals, "Rooms WHERE room_id = '%d' AND room_name = '%s'",
             ((t_renew *)(lst->data))->room_id,
             ((t_renew *)(lst->data))->name_room);
    rs = mx_model_select("id", vals, callback_check_msg, NULL);
    return rs;
}

void mx_contr_update_rooms(json_object *jobj) {
    t_renew *udata = (t_renew *)malloc(sizeof(t_renew));
    memset(udata, 0, sizeof(t_renew));
    t_list *lst = (t_list *)malloc(sizeof(t_list));
    char *vals;

    lst =  mx_create_node(udata);
    json_parse(jobj, lst);
    mx_pop_front(&lst);
    if (lst) {
        while (lst) {
            if (mx_check_msgs(lst) != 1) {
                asprintf(&vals, "'%d','%s'",
                         ((t_renew *)(lst->data))->room_id,
                         ((t_renew *)(lst->data))->name_room);
                mx_model_insert("Rooms", "room_id, room_name", vals);
            }
            lst = lst->next;
        }
    }
}
