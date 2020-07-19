#include "header.h"

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: %s <port>\n", argv[0]);
		return EXIT_FAILURE;
	}
	int port = atoi(argv[1]);

    mx_server_socket(port);
	return 0;
}
