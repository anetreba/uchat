#include "header.h"

void new_room(GtkButton *button, t_event *event) {
    t_list_room *room = (t_list_room *)malloc(sizeof(t_list_room));

    memset(room, 0, sizeof(t_list_room));
    room->room_name = strdup("new_room");

    room->row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    room->room_btn = gtk_button_new_with_label(room->room_name);

    gtk_widget_set_hexpand(room->room_btn, TRUE);
    gtk_widget_set_halign(room->room_btn, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(room->room_btn, GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(room->room_btn, 60, 5);
    gtk_container_add(GTK_CONTAINER(room->row), room->room_btn);

    gtk_list_box_insert(GTK_LIST_BOX(event->gtk->list_rooms), room->row, -1);

    gtk_widget_show(room->row);
    gtk_widget_show(room->room_btn);

    mx_push_back(&(event->list_room), room);

    (void)button;
}

