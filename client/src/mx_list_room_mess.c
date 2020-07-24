#include "header.h"

void mx_front_message(int room_id, t_event *event) {
    t_list *lst = event->list_room;

    while (lst) {
        if (((t_list_room *)(lst->data))->room_id == room_id) {
            while (((t_list_room *)(lst->data))->mess) {
                ((t_mess *)((t_list_room *)(lst->data))->mess->data)->row_user = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
                ((t_mess *)((t_list_room *)(lst->data))->mess->data)->row_msg = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

                ((t_mess *)((t_list_room *)(lst->data))->mess->data)->message_button = gtk_button_new_with_label(((t_mess *)((t_list_room *)(lst->data))->mess->data)->message);
                gtk_widget_set_hexpand(((t_mess *)((t_list_room *)(lst->data))->mess->data)->message_button, TRUE);
                if (((t_mess *)((t_list_room *)(lst->data))->mess->data)->sender_id == event->data->id)
                    gtk_widget_set_halign(((t_mess *)((t_list_room *)(lst->data))->mess->data)->message_button, GTK_ALIGN_END); // <---- END - твои сообщения, START пришедшие
                else
                    gtk_widget_set_halign(((t_mess *)((t_list_room *)(lst->data))->mess->data)->message_button, GTK_ALIGN_START);
                gtk_widget_set_valign(((t_mess *)((t_list_room *)(lst->data))->mess->data)->message_button, GTK_ALIGN_CENTER);
                gtk_widget_set_size_request(((t_mess *)((t_list_room *)(lst->data))->mess->data)->message_button, 300, 5);
                gtk_container_add(GTK_CONTAINER(((t_mess *)((t_list_room *)(lst->data))->mess->data)->row_user),((t_mess *)((t_list_room *)(lst->data))->mess->data)->message_button);

                ((t_mess *)((t_list_room *)(lst->data))->mess->data)->user_button = gtk_button_new_with_label(((t_mess *)((t_list_room *)(lst->data))->mess->data)->sender_nick); //who send a message
                gtk_widget_set_hexpand(((t_mess *)((t_list_room *)(lst->data))->mess->data)->user_button, TRUE);
                if (((t_mess *)((t_list_room *)(lst->data))->mess->data)->sender_id == event->data->id)
                    gtk_widget_set_halign(((t_mess *)((t_list_room *)(lst->data))->mess->data)->user_button, GTK_ALIGN_END); // <---- END - твой ник, START кто прислал
                else
                    gtk_widget_set_halign(((t_mess *)((t_list_room *)(lst->data))->mess->data)->user_button, GTK_ALIGN_START);
                gtk_widget_set_valign(((t_mess *)((t_list_room *)(lst->data))->mess->data)->user_button, GTK_ALIGN_CENTER);
                gtk_widget_set_size_request(((t_mess *)((t_list_room *)(lst->data))->mess->data)->user_button, 20, 5);
                gtk_widget_set_opacity(((t_mess *)((t_list_room *)(lst->data))->mess->data)->user_button, 1);
                gtk_container_add(GTK_CONTAINER(((t_mess *)((t_list_room *)(lst->data))->mess->data)->row_msg), ((t_mess *)((t_list_room *)(lst->data))->mess->data)->user_button);

                gtk_list_box_insert(GTK_LIST_BOX(event->gtk->list_box), ((t_mess *)((t_list_room *)(lst->data))->mess->data)->row_msg, -1);
                gtk_list_box_insert(GTK_LIST_BOX(event->gtk->list_box), ((t_mess *)((t_list_room *)(lst->data))->mess->data)->row_user, -1);

                gtk_widget_show(event->gtk->list_box);

                gtk_widget_show(((t_mess *)((t_list_room *)(lst->data))->mess->data)->row_msg);
                gtk_widget_show(((t_mess *)((t_list_room *)(lst->data))->mess->data)->user_button);

                gtk_widget_show(((t_mess *)((t_list_room *)(lst->data))->mess->data)->row_user);
                gtk_widget_show(((t_mess *)((t_list_room *)(lst->data))->mess->data)->message_button);

                ((t_list_room *)(lst->data))->mess = ((t_list_room *)(lst->data))->mess->next;
            }
        }
        lst = lst->next;
    }
}

void mx_select_room(GtkButton *button, t_event *event) {
    t_list_room *room = g_object_get_data(G_OBJECT(button), "room"); // берем указатель на комнату
    printf("%d\n", room->room_id);
    gtk_widget_destroy(event->gtk->row_user);
    gtk_widget_destroy(event->gtk->row_msg);

    mx_front_message(room->room_id, event);
}

void mx_parse_room_front(t_event *event) {
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
}

