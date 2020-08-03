#include "header.h"


void mx_charge_tokens(t_event *event) {
    event->gtk->tokens = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "tokens_lbl"));
    if (event->tokens > 0) {
        char *tokens = mx_strjoin("Tokens: ", mx_itoa(event->tokens));
        printf("TOKENS = %s\n", tokens);
        gtk_label_set_text(GTK_LABEL(event->gtk->tokens), tokens);
    }
}

gboolean mx_add_mess_to_list(void *data) {
    t_event *event = (t_event *)data;
    t_list *lst = event->list_room;

    while (lst) {
        if (((t_list_room *)(lst->data))->room_id == event->send_message->room_id) {
            printf("ROOM = %d\n", event->send_message->room_id);
            t_mess *mess = (t_mess *)malloc(sizeof(t_mess));

            mess->sender_id = event->send_message->sender_id;
            mess->date_send = event->send_message->date_send;
            mess->type = event->send_message->type;
            mess->message = strdup(event->send_message->message);
            mess->sender_nick = strdup(event->send_message->nick);

            mess->row_user = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
            mess->row_msg = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

            mess->message_button = gtk_button_new_with_label(mess->message);
            gtk_widget_set_name(mess->message_button, "message_button");

            gtk_widget_set_hexpand(mess->message_button, TRUE);
            if (mess->sender_id == event->data->id) {
                gtk_widget_set_halign(mess->message_button, GTK_ALIGN_END);
            } // <---- END - твои сообщения, START пришедшие
            else {
                gtk_widget_set_halign(mess->message_button, GTK_ALIGN_START);
            }
            gtk_widget_set_valign(mess->message_button, GTK_ALIGN_CENTER);
            gtk_widget_set_size_request(mess->message_button, 300, 5);
            gtk_container_add(GTK_CONTAINER(mess->row_user),mess->message_button);

            mess->user_button = gtk_button_new_with_label(mess->sender_nick); //who send a message
            gtk_widget_set_hexpand(mess->user_button, TRUE);
            gtk_widget_set_name(mess->user_button, "sender");

            if (mess->sender_id == event->data->id) {
                gtk_widget_set_halign(mess->user_button, GTK_ALIGN_END);
            } // <---- END - твой ник, START кто прислал
            else {
                gtk_widget_set_halign(mess->user_button, GTK_ALIGN_START);
            }
            gtk_widget_set_valign(mess->user_button, GTK_ALIGN_CENTER);
            gtk_widget_set_size_request(mess->user_button, 20, 5);
            gtk_widget_set_opacity(mess->user_button, 1);
            gtk_container_add(GTK_CONTAINER(mess->row_msg), mess->user_button);

            gtk_list_box_insert(GTK_LIST_BOX(((t_list_room *)(lst->data))->list_box), mess->row_msg, -1);
            gtk_list_box_insert(GTK_LIST_BOX(((t_list_room *)(lst->data))->list_box), mess->row_user, -1);

            //gtk_widget_show(((t_list_room *)(lst->data))->list_box);

            printf("error\n");
            gtk_widget_show(mess->row_msg);
            gtk_widget_show(mess->user_button);

            gtk_widget_show(mess->row_user);
            gtk_widget_show(mess->message_button);


            mx_push_back(&(((t_list_room *)(lst->data))->mess), mess);
        }
        lst = lst->next;
    }
    mx_charge_tokens(event);
    return 0;
}

static int callback_sender(void *data, int argc, char **argv, char **ColName) {
    t_send_message *udata = (t_send_message *)data;
    ColName = NULL;

    if (argc > 0 && argv) {
        udata->nick = strdup(argv[0]);
    }
    return 0;
}


void mx_select_new_message(t_event *event) {
    char *vals;

    asprintf(&vals, "Contacts WHERE user_id = '%d'", event->send_message->sender_id);
    mx_model_select("nick", vals, callback_sender, event->send_message);
}

static void write_auth_data(t_event *event, json_object *obj) {
    struct json_object *room_id;
    struct json_object *message;
    struct json_object *sender_id;
    struct json_object *date_send;
    struct json_object *tokens;

    event->send_message = (t_send_message *)malloc(sizeof(t_send_message));
    memset(event->send_message, 0, sizeof(t_send_message));

    json_object_object_get_ex(obj, "room_id", &room_id);
    json_object_object_get_ex(obj, "message", &message);
    json_object_object_get_ex(obj, "sender_id", &sender_id);
    json_object_object_get_ex(obj, "date_send", &date_send);
    json_object_object_get_ex(obj, "tokens", &tokens);

    event->send_message->room_id = json_object_get_int(room_id);
    event->send_message->message = (char *)json_object_get_string(message);
    event->send_message->sender_id = json_object_get_int(sender_id);
    event->send_message->date_send = json_object_get_int(date_send);
    event->tokens = json_object_get_int(tokens);


    mx_model_new_message(event->send_message);
    mx_select_new_message(event);
 //   mx_add_mess_to_list(event);
//    mx_print(event->list_room);
    gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_add_mess_to_list, event, 0);
    // mx_json(event, "renew_rooms");

}

void mx_contr_new_message(t_event *event, json_object *jobj) {
    struct json_object *obj = json_object_new_object();
    const char *jstr = json_object_to_json_string(jobj);

    parse_json((const char *)jstr, &obj);
    write_auth_data(event, obj);
}
