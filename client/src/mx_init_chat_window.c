#include "header.h"

gboolean show_error_label(void *data) {
    t_event *event = (t_event *)data;

    GtkWidget *error_label = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "wrong_pass_lbl"));
    gtk_label_set_text(GTK_LABEL(error_label), "Wrong Login or Password");
    printf("Wrong login or Password\n");
    gtk_widget_show(error_label);
    return 0;
}

//void hide_contacts(GtkButton *button, t_event *event) {
//    gtk_widget_hide(event->gtk->contacts_wdw);
//    (void)button;
//}

//void add_new_contact(GtkButton *button, t_event *event) {
//    //TODO: add new contact in box_list
//    printf("add new contacts\n");
//
//    (void)event;
//
//    (void)button;
//}

//void show_contacts_wdw(GtkButton *button, t_event *event) {
//    event->gtk->contacts_back_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder4, "contacts_back_btn"));
//    event->gtk->new_contact_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder4, "new_contact_btn"));
//
//    gtk_widget_show(event->gtk->contacts_wdw);
//
//    mx_contr_select_contacts(event);
//    //TODO: show list of all contacts
//
////    t_list *lst = (t_list *)event->data;
////
////    while (lst) {
////        printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!login: %s\n", ((t_event *)event)->data->login);
////        lst = lst->next;
////    }
//
//    g_signal_connect(event->gtk->contacts_back_btn, "clicked", G_CALLBACK(hide_contacts), event);
//    g_signal_connect(event->gtk->new_contact_btn, "clicked", G_CALLBACK(add_new_contact), event);
//
//    (void)button;
//}

void show_groups_wdw(GtkButton *button, t_event *event) {
    gtk_widget_show(event->gtk->groups_wdw);

    //TODO: show list of contacts and groups

    (void)button;
}

void chat_window(t_event *event) {
    event->gtk->chat_window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_window"));

    event->gtk->chat_send_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_send_btn"));
    event->gtk->msg = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_entry_message"));
    gtk_widget_hide(event->gtk->chat_send_btn);
    gtk_widget_hide(event->gtk->msg);

    event->gtk->scrolled_window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "scrolled_window"));
    event->gtk->viewport = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "viewport"));

    event->gtk->contacts = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "contacts_btn"));
    event->gtk->new_room = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "new_room_btn"));
    event->gtk->contacts_wdw = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder4, "contacts_wdw"));
    event->gtk->groups_wdw = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder5, "groups_wdw"));

    event->gtk->list_rooms = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "list_rooms"));

    g_signal_connect(event->gtk->chat_send_btn, "clicked", G_CALLBACK(send_messages), event);
    g_signal_connect(event->gtk->new_room, "clicked", G_CALLBACK(show_groups_wdw), event);
    g_signal_connect(event->gtk->contacts, "clicked", G_CALLBACK(show_contacts_wdw), event);
}

gboolean mx_show_chat_window(void *data) {
    t_event *event = (t_event *)data;

    gtk_widget_hide(event->gtk->window);
    gtk_widget_show(event->gtk->chat_window);
    return 0;
}
