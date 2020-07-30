#include "header.h"

void hide_quit_wdw(GtkButton *button, t_event *event) {
    gtk_widget_hide(event->gtk->quit_wdw);

    (void)button;
}

void logout(GtkButton *button, t_event *event) {
    gtk_entry_set_text(GTK_ENTRY(event->gtk->login), "");
    gtk_entry_set_text(GTK_ENTRY(event->gtk->pass), "");

    gtk_widget_hide(event->gtk->quit_wdw);
    gtk_widget_hide(event->gtk->chat_window);
    gtk_widget_show(event->gtk->window);
    (void)button;
}

void show_logout_wdw(GtkButton *button, t_event *event) {
    (void)button;
    event->gtk->quit_wdw = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder6, "quit_wdw"));
    event->gtk->yes_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder6, "yes_btn"));
    event->gtk->no_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder6, "no_btn"));

    gtk_widget_show(event->gtk->quit_wdw);
    gtk_widget_show(event->gtk->yes_btn);
    gtk_widget_show(event->gtk->no_btn);

    g_signal_connect(event->gtk->yes_btn, "clicked", G_CALLBACK(logout), event);
    g_signal_connect(event->gtk->no_btn, "clicked", G_CALLBACK(hide_quit_wdw), event);
}
