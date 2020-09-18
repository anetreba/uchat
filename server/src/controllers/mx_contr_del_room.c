#include "header.h"

void *mx_contr_del_room(t_edit_room *room) {
    char *condition;

    asprintf(&condition, "id = %d AND user_id", room->room_id);
    mx_model_del("Rooms", condition);
    return 0;
}
