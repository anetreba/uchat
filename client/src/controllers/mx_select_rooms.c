#include "header.h"

static int callback_rooms(void *data, int argc, char **argv, char **ColName) {
    t_data *udata = (t_data *)data;
    ColName = NULL;

    if (argc > 0 && argv) {
        udata->id = atoi(argv[0]);
        udata->name_room = strdup(argv[1]);
    }
    return 0;
}

int mx_select_rooms(t_list *lst) {
    char *vals;
    char *str;
    char *auth_token = NULL;
    t_data data;
    int rs;

    asprintf(&vals, "Rooms GROUP BY id");

    rs = mx_model_select("DISTINCT id, name", vals, callback_rooms, &data);
    return rs;
}

