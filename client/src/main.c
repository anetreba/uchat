#include "header.h"

void mx_json(struct json_object *jobj) {
    //Json

    const char *question = "Mum, clouds hide alien spaceships don't they ?";
    const char *answer = "Of course not! (\"sigh\")";

    jobj = json_object_new_object();
    json_object_object_add(jobj, "question", json_object_new_string(question));
    json_object_object_add(jobj, "answer", json_object_new_string(answer));

    printf("JSON == %s\n", json_object_to_json_string(jobj));


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

	//Json

    struct json_object *jobj = NULL;


	mx_json(jobj);


///****************************************************************/
//
//    char buffer[100];
//    char output[]="client: Enter data for server: ";
//    int r = 0;
//
//    while(strcmp(buffer,"quit") != 0) {
//        bzero(buffer,100);
//        write(1, output, strlen(output));
//        r = read(0 , buffer, sizeof(buffer));
//        buffer[r - 1]='\0';
//        write(network_socket, buffer, strlen(buffer));
//    }
//
///****************************************************************/
	char info_from_server[256];
	recv(network_socket, &info_from_server, sizeof(info_from_server), 0);

	printf("THE SERVER DATA -- %s\n", info_from_server);

	close(network_socket);




	return 0;
}
