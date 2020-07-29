#include "header.h"

void back_to_chat(GtkButton *button, t_event *event) {
    gtk_widget_hide(event->gtk->groups_wdw);
    (void)button;
}

void room_confirm_btn(GtkButton *button, t_event *event) {
    event->info_room->room_name = (char *)(gtk_entry_get_text(GTK_ENTRY(event->gtk->add_room_entry_field)));

    mx_json(event, "add_room");
    gtk_widget_hide(event->gtk->groups_wdw);
    printf("ROOM_NAME = %s\n", event->info_room->room_name);
    (void)button;
}

void mx_select_cont(GtkButton *button, t_event *event) {
    t_cont_for_add_room *cont = g_object_get_data(G_OBJECT(button), "cont");

    t_cont *add_cont = (t_cont *)malloc(sizeof(t_cont));

    add_cont->nick = strdup(cont->nick);
    add_cont->id = cont->id;
    mx_push_back(&(event->info_room->cont), add_cont);
    printf("NICK = %s\n", add_cont->nick);
    printf("ID = %d\n", cont->id);
    mx_push_back(&(event->info_room->cont), add_cont);
    gtk_widget_hide(GTK_WIDGET(button));
    (void)button;
}

gboolean mx_render_cont(void *data) {
    t_event *event = (t_event *)data;
    t_list *lst = event->list_contact;

    while (lst) {
        t_cont_for_add_room *cont = (t_cont_for_add_room *) malloc(sizeof(t_cont_for_add_room));
        cont->id = ((t_renew_contacts *)(lst->data))->contact_id;
        cont->nick = strdup(((t_renew_contacts *)(lst->data))->nickname);

        cont->row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
        cont->cont_btn = gtk_button_new_with_label(cont->nick);
        g_object_set_data(G_OBJECT(cont->cont_btn), "cont", cont); //создание указателя на комнату

        gtk_widget_set_hexpand(cont->cont_btn, TRUE);
        gtk_widget_set_halign(cont->cont_btn, GTK_ALIGN_CENTER);
        gtk_widget_set_valign(cont->cont_btn, GTK_ALIGN_CENTER);
        gtk_widget_set_size_request(cont->cont_btn, 60, 5);
        gtk_container_add(GTK_CONTAINER(cont->row), cont->cont_btn);

        gtk_list_box_insert(GTK_LIST_BOX(event->gtk->users_listbox), cont->row, 1);

        gtk_widget_show(cont->row);
        gtk_widget_show(cont->cont_btn);
        g_signal_connect(cont->cont_btn, "clicked", G_CALLBACK(mx_select_cont), event);
        mx_push_back(&(event->for_new_room), cont);
        lst = lst->next;
    }
    return 0;
}

void mx_show_groups_wdw(GtkButton *button, t_event *event) {

    gtk_widget_show(event->gtk->groups_wdw);
//    event->gtk->add_room_entry_field = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder5, "entry_settings_field"));
//    event->gtk->add_room_back_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder5, "back_settings_btn"));
//    event->gtk->add_room_confirm_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder5, "confirm_settings_btn"));
//    event->gtk->users_listbox = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder5, "users_listbox_settings"));

//    mx_render_cont(event);

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

