#include "header.h"

//static char *result(char *s1,  char *s2) {
//    char *res = NULL;
//    res = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
//    res = mx_strcat(res, s1);
//    res = mx_strcat(res, s2);
//    if (malloc_size(s1))
//        mx_strdel(&s1);
//    return res;
//}
//
//char *mx_strjoin_two(char *s1,  char *s2) {
//    char *res = NULL;
//
//    if (!s1 && !s2)
//        return NULL;
//    else if (!s1) {
//        res = mx_strnew(mx_strlen(s2));
//        res = mx_strcat(res, s2);
//    }
//    else if (!s2) {
//        res = mx_strnew(mx_strlen(s1));
//        res = mx_strcat(res, s1);
//        mx_strdel(&s1);
//    }
//    else
//        res = result(s1, s2);
//    return res;
//}



static int parse_json(const char *json, json_object **responses) {
    json_tokener *tok = json_tokener_new();

    int stringlen = 0;
    enum json_tokener_error jerr;
    do {
        stringlen = strlen(json);
        *responses = json_tokener_parse_ex(tok, json, stringlen);
    } while ((jerr = json_tokener_get_error(tok)) == json_tokener_continue);

    if (jerr != json_tokener_success) {
        fprintf(stderr, "JSON Error: %s\n", json_tokener_error_desc(jerr));
        return 1;
    }

    json_tokener_free(tok);

    return 0;
}

void mx_parse_str(char *jstr, char buf) {
    char *tmp = mx_strnew(mx_strlen(jstr) + 1);
    printf("%c\n", buf);
    tmp[mx_strlen(jstr) + 1] = buf;
    printf("malloc size = %d\n", mx_strlen(jstr));
    printf("tmp[mal] = %c\n", tmp[mx_strlen(jstr) + 1]);
    printf("tmp = %s\n", tmp);
    mx_strdel(&jstr);
    jstr = mx_strdup(tmp);
    mx_strdel(&tmp);
}

static void* ws_establishconnection(void *vsock) {
    int sock = (int)(intptr_t)vsock;  /* File descriptor.               */
    int n;                           /* Number of bytes sent/received. */
    char buf;
    char *jstr = mx_strnew(1);
    struct json_object *jobj = json_object_new_object();
    printf("\n************************************************\n");

    while ((n = read(sock, &buf, 1)) > 0) {
        mx_parse_str(jstr, buf);
        //jstr = mx_strjoin_two(jstr, &buf);
        printf("jstr = %s\n", jstr);
        if (jstr[mx_strlen(jstr) - 2] == '}') {
//            for (int i = 0; jstr[i]; i++) {
//                printf("%c\n", jstr[i]);
//            }
            const char *jstr1 = "{ \"question\": \"Mum, clouds hide alien spaceships don't they ?\", \"answer\": \"Of course not! (\\\"sigh\\\")\" }";
            for (int i = 0; jstr1[i]; i++) {
                printf("%c\n",jstr1[i]);
            }
            printf("len jstr == %d\n", mx_strlen(jstr));
            printf("len jstr1 == %d\n", mx_strlen(jstr1));
            if (parse_json((const char *)jstr, &jobj)) {
                printf("Failed to parse JSON responses.\n");
            }
            printf("JSON = %s\n", json_object_to_json_string(jobj));

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
