#include "header.h"

gboolean show_error_label(void *data) {
    t_event *event = (t_event *)data;

    GtkWidget *error_label = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "wrong_pass_lbl"));
    gtk_label_set_text(GTK_LABEL(error_label), "Wrong Login or Password");
    printf("Wrong login or Password\n");
    gtk_widget_show(error_label);
    return 0;
}

void hide_quit_wdw(GtkButton *button, t_event *event) {
    gtk_widget_hide(event->gtk->quit_wdw);

    (void)button;
}

void hide_edit_profile(GtkButton *button, t_event *event) {
    gtk_widget_hide(event->gtk->edit_profile_wdw);

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
///////////////////////////////////////////////////////////////////////////////////////////////////
void edit_profile_confirm(GtkButton *button, t_event *event) {
//    memset(event->edit_prof, 0, sizeof(t_edit_prof));

    event->edit_prof->edit_login = gtk_entry_get_text(GTK_ENTRY(event->gtk->edit_login));
    event->edit_prof->edit_pass = gtk_entry_get_text(GTK_ENTRY(event->gtk->edit_pass));
    event->edit_prof->edit_email = gtk_entry_get_text(GTK_ENTRY(event->gtk->edit_email));
    event->edit_prof->edit_nick = gtk_entry_get_text(GTK_ENTRY(event->gtk->edit_nick));

    (void)button;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
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

void chat_window(t_event *event) {
    event->gtk->chat_window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_window"));

    event->gtk->chat_send_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_send_btn"));
    event->gtk->msg = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_entry_message"));
    gtk_widget_hide(event->gtk->chat_send_btn);
    gtk_widget_hide(event->gtk->msg);

    event->gtk->scrolled_window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "scrolled_window"));
    event->gtk->viewport = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "viewport"));

    event->gtk->contacts = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "contacts_btn"));
    event->gtk->new_room = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "add_room_chat_btn"));
    event->gtk->contacts_wdw = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder4, "contacts_wdw"));
    event->gtk->groups_wdw = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder5, "add_room_pop_up"));
    event->gtk->logout_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "logout_btn"));
    event->gtk->edit_profile_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "edit_profile_chat_btn"));

    event->gtk->list_rooms = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "list_rooms"));

    event->gtk->contacts_back_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder4, "contacts_back_btn"));
    event->gtk->new_contact_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder4, "new_contact_btn"));
    event->gtk->contacts_listbox = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder4, "contacts_listbox"));

    event->gtk->add_room_entry_field = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder5, "entry_settings_field"));
    event->gtk->add_room_back_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder5, "back_settings_btn"));
    event->gtk->add_room_confirm_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder5, "confirm_settings_btn"));
    event->gtk->users_listbox = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder5, "users_listbox_settings"));

//    mx_render_cont_list(event);

    //gtk_widget_show(event->gtk->contacts_wdw);
//    mx_contr_select_contacts(event);

    g_signal_connect(event->gtk->chat_send_btn, "clicked", G_CALLBACK(send_messages), event);
    g_signal_connect(event->gtk->new_room, "clicked", G_CALLBACK(mx_show_groups_wdw), event);
    g_signal_connect(event->gtk->contacts, "clicked", G_CALLBACK(show_contacts_wdw), event);
    g_signal_connect(event->gtk->logout_btn, "clicked", G_CALLBACK(show_logout_wdw), event);
    g_signal_connect(event->gtk->edit_profile_btn, "clicked", G_CALLBACK(show_edit_profile_wdw), event);
}

gboolean mx_show_chat_window(void *data) {
    t_event *event = (t_event *)data;

//    mx_contr_select_contacts(event);
    gtk_widget_hide(event->gtk->window);
    gtk_widget_show(event->gtk->chat_window);
    return 0;
}
