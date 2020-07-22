#include "header.h"

void mx_print(t_list *list);

static void write_auth_data(t_event *event, json_object *obj) {
    struct json_object *room_id;
    struct json_object *message;
    struct json_object *sender_id;
    struct json_object *date_send;

    event->send_message = (t_send_message *)malloc(sizeof(t_send_message));
    memset(event->send_message, 0, sizeof(t_send_message));

    json_object_object_get_ex(obj, "room_id", &room_id);
    json_object_object_get_ex(obj, "message", &message);
    json_object_object_get_ex(obj, "sender_id", &sender_id);
    json_object_object_get_ex(obj, "date_send", &date_send);

    event->send_message->room_id = json_object_get_int(room_id);
    event->send_message->message = json_object_get_string(message);
    event->send_message->sender_id = json_object_get_int(sender_id);
    event->send_message->date_send = json_object_get_int(date_send);

    mx_model_new_message(event->send_message);
    mx_add_mess_to_list(event);
    mx_print(event->list_room);

    // mx_json(event, "renew_rooms");

}

void mx_contr_new_message(t_event *event, json_object *jobj) {
    struct json_object *obj = json_object_new_object();
    const char *jstr = json_object_to_json_string(jobj);

    parse_json((const char *)jstr, &obj);
    write_auth_data(event, obj);
}
