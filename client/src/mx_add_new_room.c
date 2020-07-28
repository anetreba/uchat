#include "header.h"

void back_to_chat(GtkButton *button, t_event *event) {
    gtk_widget_hide(event->gtk->groups_wdw);
    (void)button;
}

void room_confirm_btn(GtkButton *button, t_event *event) {
    gtk_widget_show(event->gtk->contacts_wdw);
    event->info_room->room_name = (char *)(gtk_entry_get_text(GTK_ENTRY(event->gtk->add_room_entry_field)));
    printf("ROOM_NAME = %s\n", event->info_room->room_name);
    (void)button;
}

void mx_show_groups_wdw(GtkButton *button, t_event *event) {

    gtk_widget_show(event->gtk->groups_wdw);
    event->gtk->add_room_entry_field = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder5, "entry_settings_field"));
    event->gtk->add_room_back_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder5, "back_settings_btn"));
    event->gtk->add_room_confirm_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder5, "confirm_settings_btn"));

    event->info_room = (t_info_room *)malloc(sizeof(t_info_room));
    memset(event->info_room, 0, sizeof(t_info_room));

    g_signal_connect(event->gtk->add_room_confirm_btn, "clicked", G_CALLBACK(room_confirm_btn), event);
    g_signal_connect(event->gtk->add_room_back_btn, "clicked", G_CALLBACK(back_to_chat), event);
    //TODO: show list of contacts and groups

    (void)button;
}

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

