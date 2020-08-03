#include "header.h"

void mx_add_room_resp(t_event *event) {
    while (event->sock) {
        struct json_object *jobj = json_object_new_object();
        const char *jstr;

        json_object_object_add(jobj, "event", json_object_new_string("add_room_response"));
        json_object_object_add(jobj, "room_name",
                               json_object_new_string(event->add_room->room_name));
        json_object_object_add(jobj, "room_id",
                               json_object_new_int(event->add_room->room_id));
        json_object_object_add(jobj, "users", json_object_new_int(*event->add_room->cont_id));

        json_object *jarray = json_object_new_array();

        for (int i = 0; i < event->add_room->users_count; i++) {
            json_object *jstring = json_object_new_int(event->add_room->cont_id[i]);
            json_object_array_add(jarray, jstring);
        }

        json_object_object_add(jobj, "users", jarray);


        jstr = json_object_to_json_string(jobj);
        send(((t_sock *)(event->sock->data))->sock, jstr, strlen(jstr), 0);
        event->sock = event->sock->next;
    }
}
