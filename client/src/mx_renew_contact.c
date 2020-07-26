#include "header.h"

void hide_contacts(GtkButton *button, t_event *event) {
    gtk_widget_hide(event->gtk->contacts_wdw);
    (void)button;
}

void add_new_contact(GtkButton *button, t_event *event) {
    //TODO: add new contact in box_list
    printf("add new contacts\n");

    (void)event;

    (void)button;
}

void mx_render_cont_list(t_event *event) {
    t_list *lst = event->list_contact;

    while (lst) {
        ((t_renew_contacts *)(lst->data))->row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
        ((t_renew_contacts *)(lst->data))->cont_btn = gtk_button_new_with_label(((t_renew_contacts *)(lst->data))->nickname);
        g_object_set_data(G_OBJECT(((t_renew_contacts *)(lst->data))->cont_btn), "cont", ((t_renew_contacts *)(lst->data))); //создание указателя на комнату

        gtk_widget_set_hexpand(((t_renew_contacts *)(lst->data))->cont_btn, TRUE);
        gtk_widget_set_halign(((t_renew_contacts *)(lst->data))->cont_btn, GTK_ALIGN_CENTER);
        gtk_widget_set_valign(((t_renew_contacts *)(lst->data))->cont_btn, GTK_ALIGN_CENTER);
        gtk_widget_set_size_request(((t_renew_contacts *)(lst->data))->cont_btn, 60, 5);
        gtk_container_add(GTK_CONTAINER(((t_renew_contacts *)(lst->data))->row), ((t_renew_contacts *)(lst->data))->cont_btn);

        gtk_list_box_insert(GTK_LIST_BOX(event->gtk->contacts_listbox), ((t_renew_contacts *)(lst->data))->row, 1);

        gtk_widget_show(((t_renew_contacts *)(lst->data))->row);
        gtk_widget_show(((t_renew_contacts *)(lst->data))->cont_btn);
//        g_signal_connect(((t_renew_contacts *)(lst->data))->room_btn, "clicked", G_CALLBACK(mx_select_room), event);

        lst = lst->next;
    }
}

void show_contacts_wdw(GtkButton *button, t_event *event) {
    event->gtk->contacts_back_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder4, "contacts_back_btn"));
    event->gtk->new_contact_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder4, "new_contact_btn"));
    event->gtk->contacts_listbox = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder4, "contacts_listbox"));

    gtk_widget_show(event->gtk->contacts_wdw);

    mx_contr_select_contacts(event);
    mx_render_cont_list(event);


    g_signal_connect(event->gtk->contacts_back_btn, "clicked", G_CALLBACK(hide_contacts), event);
    g_signal_connect(event->gtk->new_contact_btn, "clicked", G_CALLBACK(add_new_contact), event);

    (void)button;
}

