#include "header.h"

static int callback_id(void *data, int argc, char **argv, char **ColName) {
    t_data *udata = (t_data *)data;
    ColName = NULL;

    if (argc > 0 && argv) {
        udata->id = atoi(argv[0]);
    }
    return 0;
}

t_event *mx_contr_add_new_room(t_event *event) {
    char *vals;
    char *str;
    t_data data;

    asprintf(&vals, "RoomsMeta", NULL);
    mx_model_select("MAX(id)", vals, callback_id, &data);
    if(data.id) {
        event->add_room->room_id = data.id;

        for (int i = 0; i < event->add_room->users_count; i++) {
            asprintf(&str, "'%d','%d','%s'", data.id, event->add_room->cont_id[i],
                     event->add_room->room_name);
            mx_model_insert("RoomsMeta", "room_id, user_id, room_name", str);
        }
    }

    return event;
}
