#include "header.h"

void hide_edit_profile(GtkButton *button, t_event *event) {
    gtk_widget_hide(event->gtk->edit_profile_wdw);

    (void)button;
}

void edit_profile_confirm(GtkButton *button, t_event *event) {
//    memset(event->edit_prof, 0, sizeof(t_edit_prof));

    event->edit_prof->edit_login = gtk_entry_get_text(GTK_ENTRY(event->gtk->edit_login));
    event->edit_prof->edit_pass = gtk_entry_get_text(GTK_ENTRY(event->gtk->edit_pass));
    event->edit_prof->edit_email = gtk_entry_get_text(GTK_ENTRY(event->gtk->edit_email));
    event->edit_prof->edit_nick = gtk_entry_get_text(GTK_ENTRY(event->gtk->edit_nick));

    (void)button;
}

void show_edit_profile_wdw(GtkButton *button, t_event *event) {
    event->gtk->edit_profile_wdw = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder7, "edit_profile_wdw"));
    event->gtk->edit_login = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder7, "edit_profile_login_entry_wdw"));
    event->gtk->edit_nick = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder7, "edit_profile_nick_entry_wdw"));
    event->gtk->edit_pass = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder7, "edit_profile_pwd_entry_wdw"));
    event->gtk->edit_email = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder7, "edit_profile_email_entry_wdw"));
    event->gtk->edit_confirm = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder7, "edit_profile_confirm_btn"));
    event->gtk->edit_back = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder7, "edit_profile_back_btn"));

    gtk_widget_show(event->gtk->edit_profile_wdw);
    g_signal_connect(event->gtk->edit_back, "clicked", G_CALLBACK(hide_edit_profile), event);
    g_signal_connect(event->gtk->edit_confirm, "clicked", G_CALLBACK(edit_profile_confirm), event);
    (void)button;
}
