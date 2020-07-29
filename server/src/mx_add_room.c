#include "header.h"

void mx_add_room(struct json_object *jobj, t_event *event) {
    struct json_object *room_name;
    json_object * jvalue;
    event->add_room = (t_info_room *)malloc(sizeof(t_info_room));

    json_object_object_get_ex(jobj, "room_name", &room_name);
    event->add_room->room_name = (char *)json_object_get_string(room_name);

    json_object *jarray = json_object_object_get(jobj, "users");

    int arraylen = json_object_array_length(jarray);
    event->add_room->cont_id = (int *)malloc(sizeof(int) * arraylen);

    for (int i = 0; i < arraylen; i++) {
        jvalue = json_object_array_get_idx(jarray, i);
        event->add_room->cont_id[i] = json_object_get_int(jvalue);
    }
    for (int i = 0; i < arraylen; i++) {
        printf("%d\n",event->add_room->cont_id[i]);
    }
}

