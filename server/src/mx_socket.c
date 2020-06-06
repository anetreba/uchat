#include "header.h"

static void* ws_establishconnection(void *vsock)
{
    int sock;                           /* File descriptor.               */
    size_t n;                           /* Number of bytes sent/received. */
    unsigned char frm[MESSAGE_LENGTH];  /* Frame.                         */
    unsigned char *msg;                 /* Message.                       */
    char *response;                     /* Response frame.                */
    int  handshaked;                    /* Handshake state.               */
    int  type;                          /* Frame type.                    */
    int  i;                             /* Loop index.                    */
    int  ret;

    handshaked = 0;
    sock = (int)(intptr_t)vsock;

    /* Receives message until get some error. */
    while ((n = read(sock, frm, sizeof(unsigned char)
                                * MESSAGE_LENGTH)) > 0) {
        /* If not handshaked yet. */
        if (!handshaked) {
            ret = getHSresponse( (char *) frm, &response);
            if (ret < 0)
                goto closed;

            handshaked = 1;
#ifdef VERBOSE_MODE
            printf("Handshaked, response: \n"
				"------------------------------------\n"
				"%s"
				"------------------------------------\n"
				,response);
#endif
            n = write(sock, response, strlen(response));
            events.onopen(sock);
            free(response);
        }
        /* Decode/check type of frame. */
        msg = ws_receiveframe(frm, n, &type);
        if (msg == NULL) {
#ifdef VERBOSE_MODE
            printf("Non text frame received from %d", sock);
			if (type == WS_FR_OP_CLSE)
				printf(": close frame!\n");
			else
			{
				printf(", type: %x\n", type);
				continue;
			}
#endif
        }

        /* Trigger events. */
        if (type == WS_FR_OP_TXT) {
            events.onmessage(sock, msg);
            free(msg);
        }
        else if (type == WS_FR_OP_CLSE) {
            free(msg);
            events.onclose(sock);
            goto closed;
        }
    }

    closed:
    /* Removes client socket from socks list. */
    pthread_mutex_lock(&mutex);
    for (i = 0; i < MAX_CLIENTS; i++) {
        if (client_socks[i] == sock) {
            client_socks[i] = -1;
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
    close(sock);

    return vsock;
}

void mx_connecion(int *client_socks, pthread_t *client_thread) {
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    memset(client_socks, -1, sizeof(client_socks));
    //Accept connections.
    while (1) {
        //Accept.
        new_open_socket = accept(sock, (struct sockaddr *)&client, (socklen_t*)&len);
        if (new_sock < 0)
            mx_printerr("Error on accepting connections..");

        //Adds client socket to socks list.
        pthread_mutex_lock(&mutex);
        for (i = 0; i < MAX_CLIENTS; i++) {
            if (client_socks[i] == -1) {
                client_socks[i] = new_open_socket;
                break;
            }
        }
        pthread_mutex_unlock(&mutex);

        if (pthread_create(&client_thread, NULL, ws_establishconnection, (void*)(intptr_t)new_sock) < 0)
            mx_printerr("Could not create the client thread!");

        pthread_detach(client_thread);
    }
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

    mx_connecion(client_socks, &client_thread);
}
