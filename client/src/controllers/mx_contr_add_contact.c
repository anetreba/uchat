#include "header.h"

static void write_auth_data(t_event *event, json_object *obj) {
    struct json_object *contact_id;
    struct json_object *nick;

//    event->add_contact = (t_add_contact *)malloc(sizeof(t_add_contact));

    memset(event->add_contact, 0, sizeof(t_add_contact));

    json_object_object_get_ex(obj, "contact_id", &contact_id);
    json_object_object_get_ex(obj, "nick", &nick);

    event->add_contact->contact_id = json_object_get_int(contact_id);
    event->add_contact->nick = json_object_get_string(nick);

    mx_model_add_contact(event->add_contact);
}

void mx_contr_add_contact(t_event *event, json_object *jobj) {
    struct json_object *obj = json_object_new_object();
    const char *jstr = json_object_to_json_string(jobj);

    parse_json((const char *)jstr, &obj);
    write_auth_data(event, obj);
}
