#include "header.h"

void mx_json(struct json_object *jobj, int network_socket, t_event *event) {
    //Json

    jobj = json_object_new_object();

    json_object_object_add(jobj, "event", json_object_new_string("sign_in"));
    json_object_object_add(jobj, "login", json_object_new_string(event->log_in->login));
    json_object_object_add(jobj, "password", json_object_new_string(event->log_in->password));
    json_object_object_add(jobj, "nick", json_object_new_string(event->log_in->nick));

    printf("Jstr == %s\n", json_object_to_json_string(jobj));

    //Send Json

    const char *jstr = json_object_to_json_string(jobj);
    printf("JSON  == %s\n", jstr);

    send(network_socket, jstr, strlen(jstr), 0);
}

void sign_up_window(GtkButton *button, GtkBuilder *builder) {
    GtkWidget *new_nickname = GTK_WIDGET(gtk_builder_get_object(builder, "entry_nick_name"));
    GtkWidget *new_login = GTK_WIDGET(gtk_builder_get_object(builder, "entry_login"));
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "sign_up_window"));
    GtkWidget *new_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_password"));
    // GtkWidget *new_email = GTK_WIDGET(gtk_builder_get_object(builder, "entry_email"));

    const char *login_str = gtk_entry_get_text(GTK_ENTRY(new_login));
    const char *pass_str = gtk_entry_get_text(GTK_ENTRY(new_password));

    gtk_widget_show(window);
}

void mx_built_struct(t_event *event, const char *login_str, const char *pass_str) {
    event->log_in->login = strdup(login_str);
    event->log_in->password = strdup(pass_str);
}

void fill_sign_in(GtkButton *button, t_event *event) {

    GtkWidget *pass = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "entry_password"));
    GtkWidget *login = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "entry_login"));
    const char *login_str = gtk_entry_get_text(GTK_ENTRY(login));
    const char *pass_str = gtk_entry_get_text(GTK_ENTRY(pass));
//    event->log_in->login = strdup(login_str);
//    event->log_in->password = strdup(pass_str);
    mx_built_struct(event, login_str, pass_str);

    (void)button;
    printf("login: %s\npassword: %s\n", event->log_in->login, event->log_in->password);
//    printf("login: %s\npassword: %s\n", login_str, pass_str);

    printf("STR LOG: %s\n", login_str);
    printf("PASS LOG: %s\n", pass_str);

    // g_object_unref(G_OBJECT(builder));
}

void mx_init_login(t_event *event) {
    event->log_in = (t_log_in *)malloc(sizeof(t_log_in));
    event->gtk = (t_gtk *)malloc(sizeof(t_gtk));

    event->gtk->builder = gtk_builder_new_from_file ("src/view/login_window.glade");
    event->gtk->builder2 = gtk_builder_new_from_file ("src/view/sign_up_window.glade");
    event->gtk->window = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "login_window"));
    event->gtk->fixed = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "fixed"));
    event->gtk->sign_in_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "login_btn"));
    event->gtk->registration_btn = GTK_WIDGET(gtk_builder_get_object(event->gtk->builder, "sign_up_btn"));

    g_signal_connect (event->gtk->sign_in_btn, "clicked", G_CALLBACK(fill_sign_in), event);
    g_signal_connect (event->gtk->registration_btn, "clicked", G_CALLBACK(sign_up_window), event);
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
	int port = atoi(argv[2]);
	int network_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_adress;

	server_adress.sin_family = AF_INET;
	server_adress.sin_port = htons(port);
	server_adress.sin_addr.s_addr = inet_addr(argv[1]); //ip; //IP

	int connection_status = connect(network_socket, (struct sockaddr *)&server_adress, sizeof(server_adress));

	if (connection_status == -1) {
		printf("There was an error in connection\n");
	}

	//Events
	t_event event;
    mx_init_gtk(argc, argv, &event);

//	mx_built_struct(&event);

	//Json
	struct json_object *jobj = NULL;
	mx_json(jobj, network_socket, &event);

	int n;
    char buf;
    char *jstr = mx_strnew(0);
//    struct json_object *jobj = json_object_new_object();

    while ((n = read(network_socket, &buf, 1)) > 0) {
        jstr = mx_parse_str(jstr, buf);
    }

	printf("THE SERVER DATA -- %s\n", jstr);

	close(network_socket);

	return 0;
}
