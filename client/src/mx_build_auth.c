#include "header.h"

void build_sign_in(t_event *event) {
    event->gtk->cancel_btn_sign_in = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "cancel_btn"));
    event->gtk->pass = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "entry_password"));
    event->gtk->login = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "entry_login"));
    event->gtk->window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "login_window"));
    event->gtk->fixed = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "fixed"));
    event->gtk->sign_in_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "login_btn"));
    event->gtk->sign_up_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "sign_up_btn"));

}

void build_sign_up(t_event *event) {
    event->gtk->cancel_btn_sign_up = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder2, "cancel_btn"));
    event->gtk->new_nickname = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder2, "entry_nick_name"));
    event->gtk->new_login = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder2, "entry_login"));
    event->gtk->reg_window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder2, "sign_up_window"));
    event->gtk->new_password = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder2, "entry_password"));
    event->gtk->new_email = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder2, "entry_email"));
    event->gtk->reg_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder2, "registration_btn"));
    event->gtk->back_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder2, "back_btn"));
}
