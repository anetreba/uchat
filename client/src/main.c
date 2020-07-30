#include "header.h"

void mx_json(t_event *event, char *action) {
    char *ev[] = {"sign_in", "sign_up", "renew_rooms", "renew", "send_message", "add_contact", "renew_contacts", "add_room",
                  "edit_room", "del_room"};
    struct json_object *jobj = json_object_new_object();
    const char *jstr;
    //Json

    if (strcmp(action, ev[0]) == 0) {
        json_object_object_add(jobj, "event", json_object_new_string("sign_in"));
        json_object_object_add(jobj, "login", json_object_new_string(event->log_in->login));
        json_object_object_add(jobj, "password", json_object_new_string(event->log_in->password));
    }
    else if (strcmp(action, ev[1]) == 0) {
        json_object_object_add(jobj, "event", json_object_new_string("sign_up"));
        json_object_object_add(jobj, "login", json_object_new_string(event->sign_up->login));
        json_object_object_add(jobj, "nick", json_object_new_string(event->sign_up->nick));
        json_object_object_add(jobj, "password", json_object_new_string(event->sign_up->password));
        json_object_object_add(jobj, "email", json_object_new_string(event->sign_up->email));
    }
    else if (strcmp(action, ev[2]) == 0) {
        json_object_object_add(jobj, "event", json_object_new_string("renew_rooms"));
        json_object_object_add(jobj, "auth_token", json_object_new_string(event->data->auth_token));
    }
    else if (strcmp(action, ev[3]) == 0) {
        json_object_object_add(jobj, "event", json_object_new_string("renew"));
        json_object_object_add(jobj, "auth_token", json_object_new_string(event->data->auth_token));
    }
    else if (strcmp(action, ev[4]) == 0) {
        json_object_object_add(jobj, "event", json_object_new_string("send_message"));
        json_object_object_add(jobj, "message", json_object_new_string(event->send_message->message));
        json_object_object_add(jobj, "sender_id", json_object_new_int(event->data->id));
        json_object_object_add(jobj, "room_id", json_object_new_int(event->send_message->room_id));
        json_object_object_add(jobj, "auth_token", json_object_new_string(event->data->auth_token));
    }
    else if (strcmp(action, ev[5]) == 0) {
        json_object_object_add(jobj, "event", json_object_new_string("add_contact"));
        json_object_object_add(jobj, "nick", json_object_new_string(event->add_contact->nick));
        json_object_object_add(jobj, "sender_id", json_object_new_int(event->add_contact->sender_id));
        json_object_object_add(jobj, "auth_token", json_object_new_string(event->data->auth_token));
    }
    else if (strcmp(action, ev[6]) == 0) {
        json_object_object_add(jobj, "event", json_object_new_string("renew_contacts"));
        json_object_object_add(jobj, "auth_token", json_object_new_string(event->data->auth_token));
    }
    else if (strcmp(action, ev[7]) == 0) {
        json_object_object_add(jobj, "event", json_object_new_string("add_room"));
        json_object_object_add(jobj, "room_name", json_object_new_string(event->info_room->room_name));
        json_object *jarray = json_object_new_array();
        t_list *lst = event->info_room->cont;

        while (lst) {
            json_object *jstring = json_object_new_int(((t_cont *)(lst->data))->id);
            json_object_array_add(jarray,jstring);
            lst = lst->next;
        }
        json_object_object_add(jobj, "users", jarray);
    }
    jstr = json_object_to_json_string(jobj);
    printf("JSTR = %s\n", jstr);
    send(event->network_socket, jstr, strlen(jstr), 0);
}
//====================================================================================

void sign_up(GtkButton *button, t_event *event) {
    (void)button;
    event->sign_up = (t_sign_up *)malloc(sizeof(t_sign_up));
    event->sign_up->login = gtk_entry_get_text(GTK_ENTRY(event->gtk->new_login));
    event->sign_up->password = gtk_entry_get_text(GTK_ENTRY(event->gtk->new_password));
    event->sign_up->email = gtk_entry_get_text(GTK_ENTRY(event->gtk->new_email));
    event->sign_up->nick = gtk_entry_get_text(GTK_ENTRY(event->gtk->new_nickname));

    mx_json(event, "sign_up");
//    gtk_widget_hide(event->gtk->window);
}

void back(GtkButton *button, t_event *event) {
    (void)button;
    gtk_widget_show(event->gtk->window);
    gtk_widget_hide(event->gtk->reg_window);
}

void sign_up_window(GtkButton *button, t_event *event) {

    (void)button;
    g_signal_connect(event->gtk->reg_btn, "clicked", G_CALLBACK(sign_up), event);
    g_signal_connect(event->gtk->back_btn, "clicked", G_CALLBACK(back), event);
    gtk_widget_show(event->gtk->reg_window);
    gtk_widget_hide(event->gtk->window);

    g_signal_connect(event->gtk->reg_window , "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

void fill_sign_in(GtkButton *button, t_event *event) {

    event->log_in->login = gtk_entry_get_text(GTK_ENTRY(event->gtk->login));
    event->log_in->password = gtk_entry_get_text(GTK_ENTRY(event->gtk->pass));

    (void)button;
    printf("login: %s\npassword: %s\n", event->log_in->login, event->log_in->password);
    mx_json(event, "sign_in");
    chat_window(event);
}

void mx_init_login(t_event *event) {
    event->log_in = (t_log_in *)malloc(sizeof(t_log_in));
    event->gtk = (t_gtk *)malloc(sizeof(t_gtk));
    event->send_message = (t_send_message *)malloc(sizeof(t_send_message));
    event->edit_prof = (t_edit_prof *)malloc(sizeof(t_edit_prof));
    memset(event->log_in, 0, sizeof(t_log_in));
    memset(event->send_message, 0, sizeof(t_send_message));


    event->gtk->builder = gtk_builder_new_from_file ("src/view/login_window.glade");
    event->gtk->builder2 = gtk_builder_new_from_file ("src/view/sign_up_window.glade");
    event->gtk->builder3 = gtk_builder_new_from_file ("src/view/chat.glade");
    event->gtk->builder4 = gtk_builder_new_from_file ("src/view/contacts_window.glade");
    event->gtk->builder5 = gtk_builder_new_from_file ("src/view/add_room_pop_up.glade");
    event->gtk->builder6 = gtk_builder_new_from_file ("src/view/logout_confirm_wdw.glade");
    event->gtk->builder7 = gtk_builder_new_from_file ("src/view/edit_profile_wdw.glade");
    event->gtk->builder8 = gtk_builder_new_from_file ("src/view/settings_wdw.glade");

    //////////////////////////////////////////////////////////////////////////////////////////////
    GtkCssProvider *cssProvider  = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "src/view/style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

///////////////////////////////////////////////////////////////////////////////////////////////
    build_sign_in(event);

    event->gtk->chat_window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_window"));

    build_sign_up(event);

    g_signal_connect(event->gtk->sign_in_btn, "clicked", G_CALLBACK(fill_sign_in), event);
    g_signal_connect(event->gtk->cancel_btn_sign_in, "clicked", G_CALLBACK(cancel_sign_in), event);

    g_signal_connect(event->gtk->sign_up_btn, "clicked", G_CALLBACK(sign_up_window), event);
    g_signal_connect(event->gtk->cancel_btn_sign_up, "clicked", G_CALLBACK(cancel_sign_up), event);


    g_signal_connect(event->gtk->window , "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(event->gtk->chat_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show(event->gtk->window);
}

void mx_init_gtk(int argc, char **argv, t_event *event) {
    gtk_init(&argc, &argv);
    pthread_t x;

    mx_init_login(event);

    pthread_create(&x, NULL, mx_client_recv, (void *)event);
    gtk_main();
}

int main(int argc, char **argv) {
    if (argc != 3) {
        mx_printerr("Invalid args\n");
        return 1;
    }
    t_event event;
    int port = atoi(argv[2]);

    event.network_socket = socket(AF_INET, SOCK_STREAM, 0);
    event.prev_room_id = 0;

    struct sockaddr_in server_adress;

    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(port);
    server_adress.sin_addr.s_addr = inet_addr(argv[1]); //ip; //IP

    int connection_status = connect(event.network_socket, (struct sockaddr *)&server_adress, sizeof(server_adress));

    if (connection_status == -1) {
        printf("There was an error in connection\n");
    }

    //Events
    mx_init_gtk(argc, argv, &event);

    close(event.network_socket);

    return 0;
}
