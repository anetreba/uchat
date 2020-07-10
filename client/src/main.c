#include "header.h"

void mx_built_struct(t_event *event) {
    event->log_in = (t_log_in *)malloc(sizeof(t_log_in));
    event->log_in->login = "nas.ua";
    event->log_in->nick = "anetreba";
    event->log_in->password = "passworddd";
}

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

void fill_sign_in(GtkButton *button, GtkBuilder *builder, t_event *event) {
    GtkWidget *pass = GTK_WIDGET(gtk_builder_get_object(builder, "entry_password"));
    GtkWidget *log = GTK_WIDGET(gtk_builder_get_object(builder, "entry_login"));
    event->log_in->password = gtk_entry_get_text(GTK_ENTRY(pass));
    event->log_in->login = gtk_entry_get_text(GTK_ENTRY(log));

    printf("LOGIN = %s\n", event->log_in->login);
    printf("PASS  = %s\n", event->log_in->password);

    // g_object_unref(G_OBJECT(builder));
}

void mx_init_gtk(int argc, char **argv, t_event *event) {
    gtk_init(&argc, &argv);

    event->log_in = (t_log_in *)malloc(sizeof(t_log_in));
    // gpointer data;

    //GtkWidget	*label1;
    GtkBuilder *builder = gtk_builder_new_from_file ("src/view/uchat.glade");

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "login_window"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //gtk_builder_connect_signals(builder, NULL);

    //GtkWidget *fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
    // GtkWidget *entry_login = GTK_WIDGET(gtk_builder_get_object(builder, "entry_login"));
    // GtkWidget *entry_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_password"));
    GtkWidget *sign_in_btn = GTK_WIDGET(gtk_builder_get_object(builder, "sign_in_btn"));

    // printf("sdsdsdsds");
    g_signal_connect (sign_in_btn, "clicked", G_CALLBACK(fill_sign_in), builder);

    gtk_widget_show(window);

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
