#include "header.h"

void settings_back(GtkButton *button, t_event *event) {
    (void)button;
    gtk_widget_hide(event->gtk->settings_window);
}

void show_settings(GtkButton *button, t_event *event) {

    (void)button;
    event->gtk->settings_window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder8, "settings_wdw"));
    event->gtk->light = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder8, "light_btn"));
    event->gtk->dark = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder8, "dark_btn"));
    event->gtk->settings_back = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder8, "back_btn"));

    gtk_widget_show(event->gtk->settings_window);
    g_signal_connect(event->gtk->settings_back, "clicked", G_CALLBACK(settings_back), event);
//    g_signal_connect(event->gtk->light, "clicked", G_CALLBACK(), event);
//    g_signal_connect(event->gtk->dark, "clicked", G_CALLBACK(), event);
}
