#include "header.h"

static void write_room_data(t_event *event, json_object *obj) {
    struct json_object *room_name;
    struct json_object *room_id;
    struct json_object *users;

    event->info_room = (t_info_room *)malloc(sizeof(t_info_room));
    memset(event->info_room, 0, sizeof(t_data));
    json_object_object_get_ex(obj, "room_name", &room_name);
    json_object_object_get_ex(obj, "room_id", &room_id);
    json_object_object_get_ex(obj, "users", &users);
    event->info_room->room_name = json_object_get_string(room_name);
    event->info_room->room_id = json_object_get_int(room_id);
    mx_model_new_room(event->info_room);
}

void mx_contr_add_room(t_event *event, json_object *jobj) {
    struct json_object *obj = json_object_new_object();
    const char *jstr = json_object_to_json_string(jobj);

    send(event->network_socket, jstr, strlen(jstr), 0);
    parse_json((const char *)jstr, &obj);
    write_room_data(event, obj);
}
