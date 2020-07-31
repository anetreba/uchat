#include "header.h"

gboolean mx_show_in_cont(void *data) {
    t_event *event = (t_event *)data;

    GtkWidget *error_label = GTK_WIDGET(gtk_builder_get_object(event->gtk->add_cont_builder, "add_contact_error_lbl"));
    gtk_label_set_text(GTK_LABEL(error_label), "User in contact");
    printf("User in contact\"\n");
    gtk_widget_show(error_label);
    return 0;
}

gboolean mx_show_label_no_user(void *data) {
    t_event *event = (t_event *)data;

    GtkWidget *error_label = GTK_WIDGET(gtk_builder_get_object(event->gtk->add_cont_builder, "add_contact_error_lbl"));
    gtk_label_set_text(GTK_LABEL(error_label), "User not found");
    printf("User not found\n");
    gtk_widget_show(error_label);
    return 0;
}

gboolean mx_show_new_contact(void *data) {
    t_event *event = (t_event *)data;

    t_renew_contacts *cont = (t_renew_contacts *)malloc(sizeof( t_renew_contacts));

    cont->nickname = strdup(event->add_contact->nick);
    cont->contact_id = event->add_contact->contact_id;
    cont->row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    cont->cont_btn = gtk_button_new_with_label(cont->nickname);
    gtk_widget_set_name(cont->cont_btn, "cont_btn");

    gtk_widget_set_hexpand(cont->cont_btn, TRUE);
    gtk_widget_set_halign(cont->cont_btn, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(cont->cont_btn, GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(cont->cont_btn, 60, 5);
    gtk_container_add(GTK_CONTAINER(cont->row), cont->cont_btn);

    gtk_list_box_insert(GTK_LIST_BOX(event->gtk->contacts_listbox), cont->row, 1);

    gtk_widget_show(cont->row);
    gtk_widget_show(cont->cont_btn);
    mx_push_back(&(event->list_contact), cont);
    return 0;
}

