#include "header.h"

static void *ws_establishconnection(void *vsock) {
    t_event *event = (t_event *)vsock;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    //int sock = (int)(intptr_t)vsock;  /* File descriptor.               */
    int n;                           /* Number of bytes sent/received. */
    char buf;
    char *jstr = mx_strnew(0);
    struct json_object *jobj = json_object_new_object();

    while ((n = read(event->new_open_socket, &buf, 1)) > 0) {
        jstr = mx_parse_str(jstr, buf);
        if (jstr[mx_strlen(jstr) - 1] == '}') {
            printf("jstr = %s\n", jstr);

            if (parse_json((const char *)jstr, &jobj))
                mx_printerr("Failed to parse JSON responses.\n");
            mx_strdel(&jstr);

            printf("JSON = %s\n", json_object_to_json_string(jobj));
            jstr = mx_strnew(0);
            //JSON OBJ GET
            mx_valid_event(jobj, event);
        }
    }
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (event->client_socks[i] == event->new_open_socket) {
            event->client_socks[i] = -1;
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
    close(event->new_open_socket);
    return vsock;
}

void mx_connecion(t_event *event) {
    event->client_socks = (int *)malloc(sizeof(int));
    // int client_socks[MAX_CLIENTS]; // Mass of client sock
    // int new_open_socket; // New opened connection.
    struct sockaddr_in client; // Client.
    int len = sizeof(struct sockaddr_in);
    pthread_t client_thread; // Client thread.
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    memset(event->client_socks, -1, malloc_size(event->client_socks));
    //Accept connections.
    while (1) {
        //Accept.
        event->new_open_socket = accept(event->server_sock, (struct sockaddr *)&client, (socklen_t*)&len);
        if (event->new_open_socket < 0)
            mx_printerr("Error on accepting connections..");

        //Adds client socket to socks list.
        pthread_mutex_lock(&mutex);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (event->client_socks[i] == -1) {
                event->client_socks[i] = event->new_open_socket;
                break;
            }
        }

        pthread_mutex_unlock(&mutex);

        if (pthread_create(&client_thread, NULL, ws_establishconnection, (void*)event) < 0)
            mx_printerr("Could not create the client thread!");
        pthread_detach(client_thread);
    }
}


void mx_server_socket(int port) {
    //int sock; // Current socket. (server)
    struct sockaddr_in server; // Server.
    t_event event;

    // Create socket.
    event.server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (event.server_sock < 0)
        mx_printerr("Could not create socket");
    // Prepare the sockaddr_in structure.
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    int on = 1;
    setsockopt(event.server_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (bind(event.server_sock, (struct sockaddr *)&server, sizeof(server)) < 0)
        mx_printerr("Bind failed");
    listen(event.server_sock, MAX_CLIENTS);
    mx_connecion(&event);
}
