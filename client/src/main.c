#include "header.h"

void mx_json(t_event *event, char *action) {
    char *ev[] = {"sign_in", "sign_up", "renew_rooms", "renew"};
    struct json_object *jobj = json_object_new_object();
    const char *jstr;
    printf("1111111===============\n");
    printf("ACTION:%s\n", action);
    printf("1111111===============\n");
    //Json

    if (strcmp(action, ev[0]) == 0) {
        json_object_object_add(jobj, "event", json_object_new_string("sign_in"));
        json_object_object_add(jobj, "login", json_object_new_string(event->log_in->login));
        json_object_object_add(jobj, "password", json_object_new_string(event->log_in->password));
        jstr = json_object_to_json_string(jobj);
        send(event->network_socket, jstr, strlen(jstr), 0);
        //mx_contr_auth(event, jobj);
    }

    if (strcmp(action, ev[1]) == 0) {
        json_object_object_add(jobj, "event", json_object_new_string("sign_up"));
        json_object_object_add(jobj, "login", json_object_new_string(event->sign_up->login));
        json_object_object_add(jobj, "nick", json_object_new_string(event->sign_up->nick));
        json_object_object_add(jobj, "password", json_object_new_string(event->sign_up->password));
        json_object_object_add(jobj, "email", json_object_new_string(event->sign_up->email));
        jstr = json_object_to_json_string(jobj);
        send(event->network_socket, jstr, strlen(jstr), 0);
    }
    if (strcmp(action, ev[2]) == 0) {
        json_object_object_add(jobj, "event", json_object_new_string("renew_rooms"));
        json_object_object_add(jobj, "auth_token", json_object_new_string(event->data->auth_token));
        jstr = json_object_to_json_string(jobj);
        send(event->network_socket, jstr, strlen(jstr), 0);
    }
    if (strcmp(action, ev[3]) == 0) {
        json_object_object_add(jobj, "event", json_object_new_string("renew"));
        json_object_object_add(jobj, "auth_token", json_object_new_string(event->data->auth_token));
        jstr = json_object_to_json_string(jobj);
        send(event->network_socket, jstr, strlen(jstr), 0);
    }
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

void send_messages(GtkButton *button, t_event *event) {
    GtkWidget *msg = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_entry_message"));
    GtkWidget *list_box = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "list_box"));

    //test_label
    event->gtk->test_label = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "test_label"));

    GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *row1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

    // message buttons
    GtkWidget *new_button = gtk_button_new_with_label(event->send_message->message);
    gtk_widget_set_hexpand(new_button, TRUE);
    gtk_widget_set_halign(new_button, GTK_ALIGN_END);
    gtk_widget_set_valign(new_button, GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(new_button, 300, 5);
    gtk_container_add(GTK_CONTAINER(row), new_button);

    GtkWidget *new_button1 = gtk_button_new_with_label(event->log_in->login);
    gtk_widget_set_hexpand(new_button1, TRUE);
    gtk_widget_set_halign(new_button1, GTK_ALIGN_END);
    gtk_widget_set_valign(new_button1, GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(new_button1, 20, 5);
    gtk_widget_set_opacity(new_button1, 1);
    gtk_container_add(GTK_CONTAINER(row1), new_button1);

    event->send_message->message = gtk_entry_get_text(GTK_ENTRY(msg));
    printf("login: %s message: %s\n", event->log_in->login, event->send_message->message);

    (void)button;

    gtk_label_set_text(GTK_LABEL(event->gtk->test_label), event->log_in->login);
    gtk_entry_set_text(GTK_ENTRY(msg), "");

    gtk_list_box_insert(GTK_LIST_BOX(list_box), row1, -1);
    gtk_list_box_insert(GTK_LIST_BOX(list_box), row, -1);

    gtk_widget_show(list_box);

    gtk_widget_show(row1);
    gtk_widget_show(new_button1);

    gtk_widget_show(row);
    gtk_widget_show(new_button);
}

void chat_window(GtkButton *button, t_event *event) {
    event->gtk->chat_window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_window"));
    event->gtk->chat_send_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_send_btn"));

    gtk_widget_show(event->gtk->chat_window);
    gtk_widget_hide(event->gtk->window);
    g_signal_connect(event->gtk->chat_send_btn, "clicked", G_CALLBACK(send_messages), event);

    (void)button;
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
    //Wrong Password or login

//***************
//***************
//***************
//***************

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

//    mx_valid_event(jobj, event);
    // css_set(cssProvider, event->gtk->window);
///////////////////////////////////////////////////////////////////////////////////////////////

    event->gtk->window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "login_window"));
    event->gtk->fixed = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "fixed"));
    event->gtk->sign_in_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "login_btn"));
    event->gtk->sign_up_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "sign_up_btn"));
    event->gtk->chat_window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder3, "chat_window"));

//    mx_json_read(event);
    g_signal_connect(event->gtk->sign_in_btn, "clicked", G_CALLBACK(fill_sign_in), event);

//    if (event->data->status == 0)
//        g_signal_connect(event->gtk->sign_in_btn, "clicked", G_CALLBACK(chat_window), event);
    //if (222222)
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


//    Json
   // struct json_object *jobj = NULL;
//    mx_json(jobj, network_socket, &event);
//
//    int n;
//    char buf;
//    char *jstr = mx_strnew(0);
//    struct json_object *jobj = json_object_new_object();
//
//    while ((n = read(event.network_socket, &buf, 1)) > 0) {
//        jstr = mx_parse_str(jstr, buf);
//    }
//
//    printf("THE SERVER DATA -- %s\n", jstr);
//
//    //JSON OBJ GET
//    mx_valid_event(jobj, event);

    close(event.network_socket);

    return 0;
}
