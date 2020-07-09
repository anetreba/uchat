#include "header.h"

void mx_built_struct(t_event *event) {
    event->log_in = (t_log_in *)malloc(sizeof(t_log_in));
    event->log_in->login = "hellboy2020";
    event->log_in->nick = "ovoitenko";
    event->log_in->password = "password";
}

void mx_json(struct json_object *jobj, int network_socket, t_event *event) {
    //Json
    event = NULL;
    jobj = json_object_new_object();

//    json_object_object_add(jobj, "event", json_object_new_string("sign_in"));
//    json_object_object_add(jobj, "login", json_object_new_string(event->log_in->login));
//    json_object_object_add(jobj, "password", json_object_new_string(event->log_in->password));
//    json_object_object_add(jobj, "nick", json_object_new_string(event->log_in->nick));

    json_object_object_add(jobj, "event", json_object_new_string("renew"));
    json_object_object_add(jobj, "auth_token", json_object_new_string("djbEHKvrLK5t5pJqPyehHGCc"));
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

	int n;
    char buf = 0;
    char *jstr = mx_strnew(0);
//    struct json_object *jobj = json_object_new_object();

    while ((n = read(network_socket, &buf, 1)) > 0) {
        jstr = mx_parse_str(jstr, buf);
        if (jstr[strlen(jstr) - 1] == '}')
            break;
    }

    printf("THE SERVER DATA -- %s\n", jstr);

	close(network_socket);

	return 0;
}
