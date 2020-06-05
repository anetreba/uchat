#include "header.h"

void mx_connecion() {

}


void mx_server_socket(int port) {
    int sock; // Current socket. (server)
    int new_open_socket; // New opened connection.
    struct sockaddr_in server; // Server.
    struct sockaddr_in client; // Client.
    pthread_t client_thread; // Client thread.
    int client_socks[MAX_CLIENTS]; // Mass of client sock

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


    memset(client_socks, -1, sizeof(client_socks));
    /* Accept connections. */
    while (1) {
        /* Accept. */
        new_open_socket = accept(sock, (struct sockaddr *)&client, (socklen_t*)&len);
        if (new_sock < 0)
            panic("Error on accepting connections..");

        /* Adds client socket to socks list. */
        pthread_mutex_lock(&mutex);
        for (i = 0; i < MAX_CLIENTS; i++) {
            if (client_socks[i] == -1) {
                client_socks[i] = new_open_socket;
                break;
            }
        }
        pthread_mutex_unlock(&mutex);

        if (pthread_create(&client_thread, NULL, ws_establishconnection,
                           (void*)(intptr_t) new_sock) < 0)
            panic("Could not create the client thread!");

        pthread_detach(client_thread);
    }
}
