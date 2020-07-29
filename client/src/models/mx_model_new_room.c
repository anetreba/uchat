#include "header.h"

void mx_model_new_room(t_info_room *info_room) {
    char *vals;

    if (info_room) {
        asprintf(&vals, "'%s','%d'", info_room->room_name, info_room->room_id);
        mx_model_insert("Rooms", "room_name, room_id", vals);
    }
}
