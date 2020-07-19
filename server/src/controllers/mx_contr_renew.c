#include "header.h"

static int callback_renew(void *data, int argc, char **argv, char **ColName) {
    t_list *lst = (t_list *)data;
    data = NULL;
    ColName = NULL;
    t_upd *udata = (t_upd *)malloc(sizeof(t_upd));

    if (argc > 0 && argv) {
        udata->message = strdup(argv[0]);
        udata->room_id = atoi(argv[1]);
        udata->room_name = strdup(argv[2]);
        udata->sender_id = atoi(argv[3]);
        udata->date_send = atoi(argv[4]);
        udata->recieve_status = atoi(argv[5]);
        mx_push_back(&lst, udata);
    }
    return 0;
}

t_list *mx_contr_renew(t_renew *tok) {
    char *vals;
    t_upd *udata = (t_upd *)malloc(sizeof(t_upd));
    memset(udata, 0, sizeof(t_upd));
    t_list *data =  mx_create_node(udata);
    int rs;

    asprintf(&vals, "Messages, Rooms "
                    "WHERE Rooms.room_id = (SELECT DISTINCT "
                    "room_id FROM Messages WHERE sender_id = ("
                    "SELECT id FROM Users WHERE auth_token = '%s') "
                    "GROUP BY Messages.room_id)", tok->auth_token);
    rs = mx_model_select("DISTINCT Messages.message,"
                         "    Messages.room_id,"
                         "    Rooms.room_name,"
                         "    Messages.sender_id,"
                         "    Messages.date_send,"
                         "    Messages.recieve_status",
                         vals, callback_renew, data);
    mx_pop_front(&data);
    free(vals);
    return data;
}
