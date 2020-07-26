#include "header.h"

gboolean show_error_label(void *data) {
    t_event *event = (t_event *)data;

    GtkWidget *error_label = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "wrong_pass_lbl"));
    gtk_label_set_text(GTK_LABEL(error_label), "Wrong Login or Password");
    printf("Wrong login or Password\n");
    gtk_widget_show(error_label);
    return 0;
}

void chat_window(t_event *event) {
    event->gtk->chat_window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_window"));

    event->gtk->chat_send_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_send_btn"));
    event->gtk->msg = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_entry_message"));
    gtk_widget_hide(event->gtk->chat_send_btn);
    gtk_widget_hide(event->gtk->msg);

    event->gtk->new_room = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "new_room_btn"));

    event->gtk->scrolled_window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "scrolled_window"));
    event->gtk->viewport = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "viewport"));

    event->gtk->list_rooms = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "list_rooms"));


    g_signal_connect(event->gtk->new_room, "clicked", G_CALLBACK(new_room), event);
}

gboolean mx_show_chat_window(void *data) {
    t_event *event = (t_event *)data;

    gtk_widget_hide(event->gtk->window);
    gtk_widget_show(event->gtk->chat_window);
    return 0;
}
