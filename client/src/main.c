#include "header.h"

void mx_json(t_event *event, char *action) {
    char *ev[] = {"sign_in", "sign_up"};
    struct json_object *jobj = json_object_new_object();
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

    //Send Json

    const char *jstr = json_object_to_json_string(jobj);
    printf("JSON  == %s\n", jstr);

    send(event->network_socket, jstr, strlen(jstr), 0);


    int n;
    char buf;
    char *str = mx_strnew(0);
    struct json_object *obj = json_object_new_object();

    while ((n = read(event->network_socket, &buf, 1)) > 0) {
        str = mx_parse_str(str, buf);
        if (str[strlen(str) - 1] == '}')
            break ;
    }
    int err = parse_json((const char *)str, &obj);
    printf("JOBJ = %s\n", json_object_to_json_string(obj));
    printf("ERR = %d\n", err);
    struct json_object *status;
    struct json_object *auth_token;
    struct json_object *tokens;

    json_object_object_get_ex(jobj, "status", &status);
    json_object_object_get_ex(jobj, "auth_token", &auth_token);
    json_object_object_get_ex(jobj, "tokens", &tokens);
    int resp = json_object_get_int(status);
    if (resp == 1)
        g_print("Wrong login/pass");
//    else if(resp[0] == 0)
//       mx_model_logined(resp);
}


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

void fill_sign_in(GtkButton *button, t_event *event) {
    GtkWidget *pass = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "entry_password"));
    GtkWidget *login = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "entry_login"));

    event->log_in->login = gtk_entry_get_text(GTK_ENTRY(login));
    event->log_in->password = gtk_entry_get_text(GTK_ENTRY(pass));

    (void)button;
    printf("login: %s\npassword: %s\n", event->log_in->login, event->log_in->password);
    mx_json(event, "sign_in");
//     g_object_unref(G_OBJECT(event->gtk->builder));
}

void mx_init_login(t_event *event) {
    event->log_in = (t_log_in *)malloc(sizeof(t_log_in));
    event->gtk = (t_gtk *)malloc(sizeof(t_gtk));
    memset(event->log_in, 0, sizeof(t_log_in));

    event->gtk->builder = gtk_builder_new_from_file ("src/view/login_window.glade");
    event->gtk->builder2 = gtk_builder_new_from_file ("src/view/sign_up_window.glade");
//////////////////////////////////////////////////////////////////////////////////////////////
    GtkCssProvider *cssProvider  = gtk_css_provider_new();
    GtkWidget *label = gtk_label_new("Label 0123456789");
    gtk_css_provider_load_from_path(cssProvider, "src/view/style.css", NULL);
    gtk_style_context_add_provider(gtk_widget_get_style_context(label),
                                   GTK_STYLE_PROVIDER(cssProvider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);
///////////////////////////////////////////////////////////////////////////////////////////////
    event->gtk->window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "login_window"));

    event->gtk->fixed = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "fixed"));
    event->gtk->sign_in_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "login_btn"));
    event->gtk->sign_up_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "sign_up_btn"));


    gtk_style_context_add_provider(gtk_widget_get_style_context(label),
                                   GTK_STYLE_PROVIDER(cssProvider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_container_add(GTK_CONTAINER(event->gtk->window), label);
    gtk_widget_show_all(event->gtk->window);

    g_signal_connect (event->gtk->sign_in_btn, "clicked", G_CALLBACK(fill_sign_in), event);
    g_signal_connect (event->gtk->sign_up_btn, "clicked", G_CALLBACK(sign_up_window), event);
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

    //Json
    //struct json_object *jobj = NULL;
    //mx_json(jobj, network_socket, &event);

//    int n;
//    char buf;
//    char *jstr = mx_strnew(0);
////    struct json_object *jobj = json_object_new_object();
//
//    while ((n = read(event.network_socket, &buf, 1)) > 0) {
//        jstr = mx_parse_str(jstr, buf);
//    }

//    printf("THE SERVER DATA -- %s\n", jstr);

    close(event.network_socket);

    return 0;
}
