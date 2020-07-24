#include "header.h"

int mx_contr_renew(t_edit_room *room) {
    char *condition;
    int rs;

    asprintf(&condition, "id = %d", room->id);
    rs = mx_model_delete("Rooms", conditions);
    free(vals);
    return rs;
}