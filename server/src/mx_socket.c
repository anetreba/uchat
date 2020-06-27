#include "header.h"

static void *ws_establishconnection(void *vsock) {
    int sock = (int)(intptr_t)vsock;  /* File descriptor.               */
    int n;                           /* Number of bytes sent/received. */
    char buf;
    char *jstr = mx_strnew(0);
    struct json_object *jobj = json_object_new_object();

    while ((n = read(sock, &buf, 1)) > 0) {
        jstr = mx_parse_str(jstr, buf);
        if (jstr[mx_strlen(jstr) - 1] == '}') {
            printf("jstr = %s\n", jstr);

            if (parse_json((const char *)jstr, &jobj))
                mx_printerr("Failed to parse JSON responses.\n");
            printf("JSON = %s\n", json_object_to_json_string(jobj));

            //JSON OBJ GET
            mx_valid_event(jobj, sock);
        }
    }
    return vsock;
}

void mx_connecion(int sock) {
    int client_socks[MAX_CLIENTS]; // Mass of client sock
    int new_open_socket; // New opened connection.
    struct sockaddr_in client; // Client.
    int len = sizeof(struct sockaddr_in);
    pthread_t client_thread; // Client thread.
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    memset(client_socks, -1, sizeof(client_socks));
    //Accept connections.
    while (1) {
        //Accept.
        new_open_socket = accept(sock, (struct sockaddr *)&client, (socklen_t*)&len);
        if (new_open_socket < 0)
            mx_printerr("Error on accepting connections..");

        //Adds client socket to socks list.
        pthread_mutex_lock(&mutex);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (client_socks[i] == -1) {
                client_socks[i] = new_open_socket;
                break;
            }
        }

        pthread_mutex_unlock(&mutex);

        if (pthread_create(&client_thread, NULL, ws_establishconnection, (void*)(intptr_t)new_open_socket) < 0)
            mx_printerr("Could not create the client thread!");

        pthread_detach(client_thread);
    }
}


void mx_server_socket(int port) {
    int sock; // Current socket. (server)
    struct sockaddr_in server; // Server.


    // Create socket.
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        mx_printerr("Could not create socket");
    // Prepare the sockaddr_in structure.
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
        mx_printerr("Bind failed");
    listen(sock, MAX_CLIENTS);
    mx_connecion(sock);
}
