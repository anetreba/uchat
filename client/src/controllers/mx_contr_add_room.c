#include "header.h"

static void write_room_data(t_event *event, json_object *obj) {
    struct json_object *room_name;
    struct json_object *room_id;
//   / struct json_object *users;

    event->info_room = (t_info_room *)malloc(sizeof(t_info_room));
    memset(event->info_room, 0, sizeof(t_data));
    json_object_object_get_ex(obj, "room_name", &room_name);
    json_object_object_get_ex(obj, "room_id", &room_id);
//    json_object_object_get_ex(obj, "users", &users);
    event->info_room->room_name = json_object_get_string(room_name);
    event->info_room->room_id = json_object_get_int(room_id);

    mx_model_new_room(event->info_room);
}



void mx_contr_add_room(t_event *event, json_object *jobj) {
   // struct json_object *obj = json_object_new_object();
   // const char *jstr = json_object_to_json_string(jobj);

//    struct json_object *room_name;
//    struct json_object *sender_id;
//    struct json_object *auth_token;
//    json_object * jvalue;

    //event->add_room = (t_info_room *)malloc(sizeof(t_info_room));
//
//    json_object_object_get_ex(jobj, "room_name", &room_name);
//    json_object_object_get_ex(jobj, "sender_id", &sender_id);
//    json_object_object_get_ex(jobj, "auth_token", &auth_token);
//    event->add_room->room_name = (char *)json_object_get_string(room_name);
//    event->add_room->sender_id = json_object_get_int(sender_id);
//    event->add_room->auth_token = (char *)json_object_get_string(auth_token);
//
//
//    json_object *jarray = json_object_object_get(jobj, "users");
//
//    int arraylen = json_object_array_length(jarray);
//
//    event->add_room->users_count = arraylen;
//    event->add_room->cont_id = (int *)malloc(sizeof(int) * arraylen);
//
//    for (int i = 0; i < arraylen; i++) {
//        jvalue = json_object_array_get_idx(jarray, i);
//        event->add_room->cont_id[i] = json_object_get_int(jvalue);
//    }
//    for (int i = 0; i < arraylen; i++) {
//        printf("%d\n",event->add_room->cont_id[i]);
//    }

//    send(event->network_socket, jstr, strlen(jstr), 0);
    //parse_json((const char *)jstr, &obj); //сигфолтит(((
    write_room_data(event, jobj);
}


