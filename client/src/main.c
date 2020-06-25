#include "header.h"

void mx_built_struct(t_event *event) {
    event->log_in = (t_log_in *)malloc(sizeof(t_log_in));
    event->log_in->login = "nas.ua";
    event->log_in->nick = "anetreba";
    event->log_in->password = "password";
}

void mx_json(struct json_object *jobj, int network_socket, t_event *event) {
    //Json

    jobj = json_object_new_object();

    json_object_object_add(jobj, "event", json_object_new_string("sing_up"));
    json_object_object_add(jobj, "login", json_object_new_string(event->log_in->login));
    json_object_object_add(jobj, "password", json_object_new_string(event->log_in->password));
    json_object_object_add(jobj, "nick", json_object_new_string(event->log_in->nick));

    printf("Jstr == %s\n", json_object_to_json_string(jobj));

    //Send Json

    const char *jstr = json_object_to_json_string(jobj);
    printf("JSON  == %s\n", jstr);

    send(network_socket, jstr, strlen(jstr), 0);
}

int main(int argc, char const **argv) {
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
	mx_built_struct(&event);

	//Json
	struct json_object *jobj = NULL;
	mx_json(jobj, network_socket, &event);

	char info_from_server[256];
	recv(network_socket, &info_from_server, sizeof(info_from_server), 0);

	printf("THE SERVER DATA -- %s\n", info_from_server);

	close(network_socket);

	return 0;
}
