#include "header.h"

void mx_json(t_event *event, char *action) {
    char *ev[] = {"sign_in", "sign_up", "renew_rooms", "renew", "send_message"};
    struct json_object *jobj = json_object_new_object();
    const char *jstr;
    //Json

    if (strcmp(action, ev[0]) == 0) {
        json_object_object_add(jobj, "event", json_object_new_string("sign_in"));
        json_object_object_add(jobj, "login", json_object_new_string(event->log_in->login));
        json_object_object_add(jobj, "password", json_object_new_string(event->log_in->password));
    }
    if (strcmp(action, ev[1]) == 0) {
        json_object_object_add(jobj, "event", json_object_new_string("sign_up"));
        json_object_object_add(jobj, "login", json_object_new_string(event->sign_up->login));
        json_object_object_add(jobj, "nick", json_object_new_string(event->sign_up->nick));
        json_object_object_add(jobj, "password", json_object_new_string(event->sign_up->password));
        json_object_object_add(jobj, "email", json_object_new_string(event->sign_up->email));
    }
    if (strcmp(action, ev[2]) == 0) {
        json_object_object_add(jobj, "event", json_object_new_string("renew_rooms"));
        json_object_object_add(jobj, "auth_token", json_object_new_string(event->data->auth_token));
    }
    if (strcmp(action, ev[3]) == 0) {
        json_object_object_add(jobj, "event", json_object_new_string("renew"));
        json_object_object_add(jobj, "auth_token", json_object_new_string(event->data->auth_token));
    }
    if (strcmp(action, ev[4]) == 0) {
        json_object_object_add(jobj, "event", json_object_new_string("send_message"));
        json_object_object_add(jobj, "message", json_object_new_string(event->send_message->message));
        json_object_object_add(jobj, "sender_id", json_object_new_int(event->data->id));
        json_object_object_add(jobj, "room_id", json_object_new_int(1));
        json_object_object_add(jobj, "auth_token", json_object_new_string(event->data->auth_token));
    }
    jstr = json_object_to_json_string(jobj);
    printf("JSTR = %s\n", jstr);
    send(event->network_socket, jstr, strlen(jstr), 0);
    mx_json_read(event);
}
//====================================================================================

void sign_up(GtkButton *button, t_event *event) {
    (void)button;
    event->sign_up = (t_sign_up *)malloc(sizeof(t_sign_up));
    event->sign_up->login = gtk_entry_get_text(GTK_ENTRY(event->gtk->new_login));
    event->sign_up->password = gtk_entry_get_text(GTK_ENTRY(event->gtk->new_password));
    event->sign_up->email = gtk_entry_get_text(GTK_ENTRY(event->gtk->new_email));
    event->sign_up->nick = gtk_entry_get_text(GTK_ENTRY(event->gtk->new_nickname));
    printf("NICK = %s\n", event->sign_up->nick);
    printf("PASSWORD = %s\n", event->sign_up->password);
    printf("EMAIL = %s\n", event->sign_up->email);
    printf("LOGIN = %s\n", event->sign_up->login);
    mx_json(event, "sign_up");
//    gtk_widget_hide(event->gtk->window);
}

void back(GtkButton *button, t_event *event) {
    (void)button;
    gtk_widget_show(event->gtk->window);
    gtk_widget_hide(event->gtk->reg_window);
}

void sign_up_window(GtkButton *button, t_event *event) {
    event->gtk->new_nickname = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder2, "entry_nick_name"));
    event->gtk->new_login = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder2, "entry_login"));
    event->gtk->reg_window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder2, "sign_up_window"));
    event->gtk->new_password = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder2, "entry_password"));
    event->gtk->new_email = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder2, "entry_email"));
    event->gtk->reg_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder2, "registration_btn"));
    event->gtk->back_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder2, "back_btn"));

    (void)button;
    g_signal_connect(event->gtk->reg_btn, "clicked", G_CALLBACK(sign_up), event);
    g_signal_connect(event->gtk->back_btn, "clicked", G_CALLBACK(back), event);
    gtk_widget_show(event->gtk->reg_window);
    gtk_widget_hide(event->gtk->window);

    g_signal_connect(event->gtk->reg_window , "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

void scroll_adjustment(t_event *event) {
    GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(event->gtk->scrolled_window));
    double value = gtk_adjustment_get_upper(adjustment);
    printf("adjustment %f\n", value);

    gtk_adjustment_set_value(adjustment, value);
}
////////////////////////////////////
void create_row(t_event *event) {
    event->gtk->row_user = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    event->gtk->row_msg = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

    // message buttons
    event->gtk->message_button = gtk_button_new_with_label(event->send_message->message);
    gtk_widget_set_hexpand(event->gtk->message_button, TRUE);
    gtk_widget_set_halign(event->gtk->message_button, GTK_ALIGN_END);
    gtk_widget_set_valign(event->gtk->message_button, GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(event->gtk->message_button, 300, 5);
    gtk_container_add(GTK_CONTAINER(event->gtk->row_user), event->gtk->message_button);

    event->gtk->user_button = gtk_button_new_with_label(event->log_in->login);
    gtk_widget_set_hexpand(event->gtk->user_button, TRUE);
    gtk_widget_set_halign(event->gtk->user_button, GTK_ALIGN_END);
    gtk_widget_set_valign(event->gtk->user_button, GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(event->gtk->user_button, 20, 5);
    gtk_widget_set_opacity(event->gtk->user_button, 1);
    gtk_container_add(GTK_CONTAINER(event->gtk->row_msg), event->gtk->user_button);
}
//////////////////////////
void send_messages(GtkButton *button, t_event *event) {
    GtkWidget *msg = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_entry_message"));
//    event->gtk->list_box = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "list_box"));

    event->send_message->message = gtk_entry_get_text(GTK_ENTRY(msg));
    create_row(event);

    // event->send_message->message = gtk_entry_get_text(GTK_ENTRY(msg));
    printf("login: %s message: %s\n", event->log_in->login, event->send_message->message);
    mx_json(event, "send_message");

    (void) button;

    // scroll_adjustment(event);

    gtk_entry_set_text(GTK_ENTRY(msg), "");
//    create_row(event);
//    gtk_list_box_insert(GTK_LIST_BOX(event->gtk->list_box), event->gtk->row_msg, -1);
//    gtk_list_box_insert(GTK_LIST_BOX(event->gtk->list_box), event->gtk->row_user, -1);

    gtk_widget_show(event->gtk->list_box);

    gtk_widget_show(event->gtk->row_msg);
    gtk_widget_show(event->gtk->user_button);

    gtk_widget_show(event->gtk->row_user);
    gtk_widget_show(event->gtk->message_button);

    scroll_adjustment(event);
}


//void new_room(GtkButton *button, t_event *event) {
//
//    GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
//
//    GtkWidget *room1 = gtk_button_new_with_label("test_room1");
//    gtk_widget_set_hexpand(room1, TRUE);
//    gtk_widget_set_halign(room1, GTK_ALIGN_CENTER);
//    gtk_widget_set_valign(room1, GTK_ALIGN_CENTER);
//    gtk_widget_set_size_request(room1, 60, 5);
//    gtk_container_add(GTK_CONTAINER(row), room1);
//
//    gtk_list_box_insert(GTK_LIST_BOX(event->gtk->list_rooms), row, -1);
//
//    gtk_widget_show(row);
//    gtk_widget_show(room1);
//
//    (void)button;
//}

void chat_window(GtkButton *button, t_event *event) {
    //rooms(event);
    event->gtk->chat_window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_window"));
    event->gtk->chat_send_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_send_btn"));
//    event->gtk->list_box = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "list_box"));
    event->gtk->new_room = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "new_room_btn"));
    event->gtk->scrolled_window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "scrolled_window"));
    event->gtk->viewport = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "viewport"));

    gtk_widget_show(event->gtk->chat_window);
    gtk_widget_hide(event->gtk->window);

    event->gtk->list_rooms = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "list_rooms"));

    mx_listroom_and_mess(event); //ROOM
    mx_parse_room_front(event);


    g_signal_connect(event->gtk->chat_send_btn, "clicked", G_CALLBACK(send_messages), event);
    g_signal_connect(event->gtk->new_room, "clicked", G_CALLBACK(new_room), event);

    (void)button;
}

void show_error_label(t_event *event) {
    GtkWidget *error_label = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "wrong_pass_lbl"));
    gtk_label_set_text(GTK_LABEL(error_label), "Wrong Login or Password");
    printf("Wrong login or Password\n");
    gtk_widget_show(error_label);
}

void fill_sign_in(GtkButton *button, t_event *event) {
    GtkWidget *pass = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "entry_password"));
    GtkWidget *login = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "entry_login"));

    event->log_in->login = gtk_entry_get_text(GTK_ENTRY(login));
    event->log_in->password = gtk_entry_get_text(GTK_ENTRY(pass));

    (void)button;
    printf("login: %s\npassword: %s\n", event->log_in->login, event->log_in->password);
    mx_json(event, "sign_in");

    //chat
    if (event->data->status == 0) {
        gtk_widget_hide(event->gtk->window);
        chat_window(button, event);
    }
    else if (event->data->status == 1)
        show_error_label(event);

    g_signal_connect(event->gtk->chat_window , "destroy", G_CALLBACK(gtk_main_quit), NULL);
//     g_object_unref(G_OBJECT(event->gtk->builder));
}

void mx_init_login(t_event *event) {
    event->log_in = (t_log_in *)malloc(sizeof(t_log_in));
    event->gtk = (t_gtk *)malloc(sizeof(t_gtk));
    event->send_message = (t_send_message *)malloc(sizeof(t_send_message));
    memset(event->log_in, 0, sizeof(t_log_in));
    memset(event->send_message, 0, sizeof(t_send_message));

    event->gtk->builder = gtk_builder_new_from_file ("src/view/login_window.glade");
    event->gtk->builder2 = gtk_builder_new_from_file ("src/view/sign_up_window.glade");
    event->gtk->builder3 = gtk_builder_new_from_file ("src/view/chat.glade");
    //////////////////////////////////////////////////////////////////////////////////////////////
    GtkCssProvider *cssProvider  = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "src/view/style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

///////////////////////////////////////////////////////////////////////////////////////////////

    event->gtk->window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "login_window"));
    event->gtk->fixed = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "fixed"));
    event->gtk->sign_in_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "login_btn"));
    event->gtk->sign_up_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "sign_up_btn"));
    event->gtk->chat_window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_window"));

    g_signal_connect(event->gtk->sign_in_btn, "clicked", G_CALLBACK(fill_sign_in), event);

    g_signal_connect(event->gtk->sign_up_btn, "clicked", G_CALLBACK(sign_up_window), event);
    g_signal_connect(event->gtk->window , "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show(event->gtk->window);
}

void mx_init_gtk(int argc, char **argv, t_event *event) {
    gtk_init(&argc, &argv);

    mx_init_login(event);

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
