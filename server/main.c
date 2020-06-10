#include "header.h"

// int main(int argc, char const **argv) {
	
// 	if (argc != 2) {
// 		printf("Usage: %s <port>\n", argv[0]);
// 		return EXIT_FAILURE;
// 	}

// 	int port = atoi(argv[1]);

// 	char server_massage[256] = "You have resached the server!\n";

// 	int server_socket = socket(AF_INET, SOCK_STREAM, 0);

// 	struct sockaddr_in server_adress;
// 	server_adress.sin_family = AF_INET;
// 	server_adress.sin_port = htons(port);
// 	server_adress.sin_addr.s_addr = INADDR_ANY;

// 	bind(server_socket, (struct sockaddr *)&server_adress, sizeof(server_adress));

// 	//второй параметр количество подключений
// 	listen(server_socket, 5);

// 	int client_socket = accept(server_socket, NULL, NULL);

// 	send(client_socket, server_massage, sizeof(server_socket), 0);
// 	close(server_socket);
// 	return 0;
// }

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: %s <port>\n", argv[0]);
		return EXIT_FAILURE;
	}
	int port = atoi(argv[1]);
	
	mx_init_sqli();
    mx_server_socket(port);
	
	return 0;
}
