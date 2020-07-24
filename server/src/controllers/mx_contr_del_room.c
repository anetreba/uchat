#include "header.h"

static int callback_users(void *data, int argc, char **argv, char **ColName) {
    t_list *lst = (t_list *)data;
    data = NULL;
    ColName = NULL;
    t_edit_room *udata = (t_edit_room *)malloc(sizeof(t_edit_room));
    if (argc > 0 && argv) {
        udata->room_id = atoi(argv[0]);
        udata->sock = atoi(argv[1]);
        mx_push_back(&lst, udata);
    }
    return 0;
}

t_list *mx_check_members(int id) {
    char *vals;
    t_renew_rooms *udata = (t_renew_rooms *)malloc(sizeof(t_renew_rooms));
    t_list *data =  mx_create_node(udata);
    memset(udata, 0, sizeof(t_renew_rooms));

    asprintf(&vals, "Users WHERE user_id = (SELECT user_id FROM RoomsMeta "
                    " WHERE room_id = '%d')"
                    " GROUP BY room_id", id);
    mx_model_select("DISTINCT sock", vals, callback_users, data);
    mx_pop_front(&data);
    free(vals);
    return data;
}

t_list *mx_contr_del_room(t_edit_room *room) {
    t_edit_room *udata = (t_edit_room *)malloc(sizeof(t_edit_room));
    t_list *data =  mx_create_node(udata);
    char *condition;

    mx_check_members(room->room_id);
    asprintf(&condition, "id = %d", room->room_id);
    mx_model_del("Rooms", condition);
    return data;
}
