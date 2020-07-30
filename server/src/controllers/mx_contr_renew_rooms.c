#include "header.h"

static int callback_renew_rooms(void *data, int argc, char **argv, char **ColName) {
    t_list *lst = (t_list *)data;
    data = NULL;
    ColName = NULL;
    t_renew_rooms *udata = (t_renew_rooms *)malloc(sizeof(t_renew_rooms));
    if (argc > 0 && argv) {
        udata->room_id = atoi(argv[0]);
        udata->room_name = strdup(argv[1]);
        mx_push_back(&lst, udata);
    }
    return 0;
}

t_list *mx_contr_renew_rooms(t_renew_rooms *tok) {
    char *vals;
    t_renew_rooms *udata = (t_renew_rooms *)malloc(sizeof(t_renew_rooms));
    t_list *data =  mx_create_node(udata);
    memset(udata, 0, sizeof(t_renew_rooms));

    asprintf(&vals, "RoomsMeta WHERE user_id = (SELECT id FROM Users "
                    " WHERE auth_token = '%s')"
                    " GROUP BY room_id", tok->auth_token);
    mx_model_select("DISTINCT room_id, room_name", vals, callback_renew_rooms, data);
    mx_pop_front(&data);
    free(vals);
    return data;
}
