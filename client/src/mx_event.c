#include "header.h"

void mx_json_read(t_event *event) {
    int n = 0;
    char buf;
    char *str = mx_strnew(0);
    struct json_object *obj = json_object_new_object();

    while ((n = read(event->network_socket, &buf, 1)) > 0) {
        str = mx_parse_str(str, buf);
        if (str[strlen(str) - 1] == '}') {
            parse_json((const char *)str, &obj);

            printf("#############################################################\n");
            printf("STR = %s\n", str);
            printf("#############################################################\n");
            mx_valid_event(obj, event);
            str = mx_strnew(0);
        }
    }
}

void mx_valid_event(struct json_object *jobj, t_event *event) {
    struct json_object *obj;
    char *events[] = {"renew_rooms_response", "renew_resp", "new_message", "signup_response",
                      "signin_response", "add_contact_response", "renew_contacts_resp",
                      "add_room_response"};
    const char *ev;

    json_object_object_get_ex(jobj, "event", &obj);
    ev = json_object_get_string(obj);
    if (strcmp(ev, events[0]) == 0) {
        mx_contr_update_rooms(jobj, event);

        struct json_object *obj = json_object_new_object();
        char *jstr;

        json_object_object_add(obj, "event", json_object_new_string("renew"));
        json_object_object_add(obj, "id", json_object_new_int(event->data->id));
        json_object_object_add(obj, "auth_token", json_object_new_string(event->data->auth_token));
        json_object_object_add(obj, "last_renew", json_object_new_int(0));
        jstr = (char *) json_object_to_json_string(obj);
        send(event->network_socket, jstr, strlen(jstr), 0);
        printf("RENEW_REQ: %s\n", jstr);
        mx_strdel(&jstr);
        return;
    }
    else if (strcmp(ev, events[1]) == 0) {
        mx_contr_renew(event, jobj);
        mx_listroom_and_mess(event);

        mx_contr_renew_contacts(event);
    }
    else if (strcmp(ev, events[2]) == 0) {
        mx_contr_new_message(event, jobj);
    }
    else if (strcmp(ev, events[3]) == 0) {
        printf("%s\n", ev);
    }
    else if (strcmp(ev, events[4]) == 0){
        mx_contr_auth(event, jobj);
    }
    else if (strcmp(ev, events[5]) == 0) {
        mx_contr_add_contact(event, jobj);
        if (event->status == 0) {
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_show_new_contact, event, 0);
        }
        else if (event->status == 1) {
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_show_label_no_user, event, 0);
        }
        else if (event->status == 2) {
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_show_in_cont, event, 0);
        }
    }
    else if (strcmp(ev, events[6]) == 0) {
        mx_model_renew_contacts(jobj);
        mx_contr_select_contacts(event);

        if (event->data->status == 0)
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_show_chat_window, event, 0);
        else
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, show_error_label, event, 0);
        gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_parse_room_front, event, 0);
        gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_render_cont_list, event, 0);
        gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_render_cont, event, 0);
    }
    else if (strcmp(ev, events[7]) == 0){
        mx_contr_add_room(event, jobj);
        gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_new_room, event, 0);
    }
}
