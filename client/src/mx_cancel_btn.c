#include "header.h"

void cancel_sign_in(GtkButton *button, t_event *event) {
    gtk_entry_set_text(GTK_ENTRY(event->gtk->login), "");
    gtk_entry_set_text(GTK_ENTRY(event->gtk->pass), "");
    (void)button;
}

void cancel_sign_up(GtkButton *button, t_event *event) {

    gtk_entry_set_text(GTK_ENTRY(event->gtk->new_nickname), "");
    gtk_entry_set_text(GTK_ENTRY(event->gtk->new_login), "");
    gtk_entry_set_text(GTK_ENTRY(event->gtk->new_password), "");
    gtk_entry_set_text(GTK_ENTRY(event->gtk->new_email), "");
    (void)button;
}

