#include "header.h"

static gint scroll(gpointer tmp) {
    t_event *event = (t_event *)tmp;
    GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(event->gtk->scrolled_window));
    double value = gtk_adjustment_get_upper(adj);

    gtk_adjustment_set_value(adj, value);
    return false;
}

void mx_print(t_list *list);

void mx_front_message(int room_id, t_event *event) {
    t_list *lst = event->list_room;

    while (lst) {
        if (((t_list_room *)(lst->data))->room_id == room_id) {
            t_list *mess = ((t_list_room *)(lst->data))->mess;

            ((t_list_room *)(lst->data))->list_box = gtk_list_box_new();
            gtk_container_add(GTK_CONTAINER(event->gtk->viewport), ((t_list_room *)(lst->data))->list_box);

            while (mess) {
                ((t_mess *)(mess->data))->row_user = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
                ((t_mess *)(mess->data))->row_msg = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

                ((t_mess *)(mess->data))->message_button = gtk_button_new_with_label(((t_mess *)(mess->data))->message);
                gtk_widget_set_hexpand(((t_mess *)(mess->data))->message_button, TRUE);
                if (((t_mess *)(mess->data))->sender_id == event->data->id)
                    gtk_widget_set_halign(((t_mess *)(mess->data))->message_button, GTK_ALIGN_END); // <---- END - твои сообщения, START пришедшие
                else
                    gtk_widget_set_halign(((t_mess *)(mess->data))->message_button, GTK_ALIGN_START);
                gtk_widget_set_valign(((t_mess *)(mess->data))->message_button, GTK_ALIGN_CENTER);
                gtk_widget_set_size_request(((t_mess *)(mess->data))->message_button, 300, 5);
                gtk_container_add(GTK_CONTAINER(((t_mess *)(mess->data))->row_user),((t_mess *)(mess->data))->message_button);

                ((t_mess *)(mess->data))->user_button = gtk_button_new_with_label(((t_mess *)(mess->data))->sender_nick); //who send a message
                gtk_widget_set_hexpand(((t_mess *)(mess->data))->user_button, TRUE);
                if (((t_mess *)(mess->data))->sender_id == event->data->id)
                    gtk_widget_set_halign(((t_mess *)(mess->data))->user_button, GTK_ALIGN_END); // <---- END - твой ник, START кто прислал
                else
                    gtk_widget_set_halign(((t_mess *)(mess->data))->user_button, GTK_ALIGN_START);
                gtk_widget_set_valign(((t_mess *)(mess->data))->user_button, GTK_ALIGN_CENTER);
                gtk_widget_set_size_request(((t_mess *)(mess->data))->user_button, 20, 5);
                gtk_widget_set_opacity(((t_mess *)(mess->data))->user_button, 1);
                gtk_container_add(GTK_CONTAINER(((t_mess *)(mess->data))->row_msg), ((t_mess *)(mess->data))->user_button);

                gtk_list_box_insert(GTK_LIST_BOX(((t_list_room *)(lst->data))->list_box), ((t_mess *)(mess->data))->row_msg, -1);
                gtk_list_box_insert(GTK_LIST_BOX(((t_list_room *)(lst->data))->list_box), ((t_mess *)(mess->data))->row_user, -1);

                gtk_widget_show(((t_list_room *)(lst->data))->list_box);

                gtk_widget_show(((t_mess *)(mess->data))->row_msg);
                gtk_widget_show(((t_mess *)(mess->data))->user_button);

                gtk_widget_show(((t_mess *)(mess->data))->row_user);
                gtk_widget_show(((t_mess *)(mess->data))->message_button);

                mess = mess->next;
            }
        }
        lst = lst->next;
    }
    g_timeout_add(200, scroll, event);
}

void mx_del_widget_mess(t_event *event) {
    if (event->prev_room_id != 0) {
        t_list *lst = event->list_room;

        while (lst) {
            if (((t_list_room * )(lst->data))->room_id == event->prev_room_id) {
                t_list *mess = ((t_list_room *)(lst->data))->mess;
                gtk_widget_hide(((t_list_room * )(lst->data))->list_box);
                gtk_container_remove(GTK_CONTAINER(event->gtk->viewport), ((t_list_room * )(lst->data))->list_box);
                while (mess) {
                    printf("CLEAR\n");
//                    gtk_container_remove(GTK_CONTAINER(((t_mess *)(mess->data))->row_msg), ((t_mess *)(mess->data))->message_button);
//                    gtk_widget_destroy(((t_mess *)(mess->data))->message_button);
//                    gtk_widget_destroy(((t_mess *)(mess->data))->user_button);
//                    gtk_widget_destroy(((t_mess *)(mess->data))->row_user);
//                    gtk_widget_destroy(((t_mess *)(mess->data))->row_msg);
                    mess = mess->next;
                }
            }
            lst = lst->next;
        }
    }
}

void send_messages(GtkButton *button, t_event *event) {
    event->send_message->message = gtk_entry_get_text(GTK_ENTRY(event->gtk->msg));

    printf("login: %s message: %s\n", event->log_in->login, event->send_message->message);

    mx_json(event, "send_message");

    (void) button;

    printf("error\n");
    gtk_entry_set_text(GTK_ENTRY(event->gtk->msg), "");

//    mx_print(event->list_room);
//    mx_add_new_message(event);

//    create_row(event);
//    gtk_list_box_insert(GTK_LIST_BOX(event->gtk->list_box), event->gtk->row_msg, -1);
//    gtk_list_box_insert(GTK_LIST_BOX(event->gtk->list_box), event->gtk->row_user, -1);

//    gtk_widget_show(event->gtk->list_box);

//    gtk_widget_show(event->gtk->row_msg);
//    gtk_widget_show(event->gtk->user_button);
//
//    gtk_widget_show(event->gtk->row_user);
//    gtk_widget_show(event->gtk->message_button);

    g_timeout_add(200, scroll, event);
}

void mx_select_room(GtkButton *button, t_event *event) {
    t_list_room *room = g_object_get_data(G_OBJECT(button), "room"); // берем указатель на комнату

    printf("prev = %d\n", event->prev_room_id);
    mx_del_widget_mess(event);

    event->prev_room_id = room->room_id;
    printf("id = %d\n", room->room_id);

    mx_front_message(room->room_id, event);

    gtk_widget_show(event->gtk->msg);
    gtk_widget_show(event->gtk->chat_send_btn);


    event->send_message->message = gtk_entry_get_text(GTK_ENTRY(event->gtk->msg));


    g_signal_connect(event->gtk->chat_send_btn, "clicked", G_CALLBACK(send_messages), event);
}

gboolean mx_parse_room_front(void *data) {
    t_event *event = (t_event *)data;
    t_list *lst = event->list_room;

    while (lst) {
        ((t_list_room *)(lst->data))->row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
        ((t_list_room *)(lst->data))->room_btn = gtk_button_new_with_label(((t_list_room *)(lst->data))->room_name);
        g_object_set_data(G_OBJECT(((t_list_room *)(lst->data))->room_btn), "room", ((t_list_room *)(lst->data))); //создание указателя на комнату

        gtk_widget_set_hexpand(((t_list_room *)(lst->data))->room_btn, TRUE);
        gtk_widget_set_halign(((t_list_room *)(lst->data))->room_btn, GTK_ALIGN_CENTER);
        gtk_widget_set_valign(((t_list_room *)(lst->data))->room_btn, GTK_ALIGN_CENTER);
        gtk_widget_set_size_request(((t_list_room *)(lst->data))->room_btn, 60, 5);
        gtk_container_add(GTK_CONTAINER(((t_list_room *)(lst->data))->row), ((t_list_room *)(lst->data))->room_btn);

        gtk_list_box_insert(GTK_LIST_BOX(event->gtk->list_rooms), ((t_list_room *)(lst->data))->row, 1);

        gtk_widget_show(((t_list_room *)(lst->data))->row);
        gtk_widget_show(((t_list_room *)(lst->data))->room_btn);
        g_signal_connect(((t_list_room *)(lst->data))->room_btn, "clicked", G_CALLBACK(mx_select_room), event);

        lst = lst->next;
    }
    return 0;
}

