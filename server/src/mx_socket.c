#include "header.h"

static int parse_json(const char *json, json_object **responses) {
    json_tokener *tok = json_tokener_new();
    int stringlen = 0;
    enum json_tokener_error jerr;

    stringlen = strlen(json);
    *responses = json_tokener_parse_ex(tok, json, stringlen);
    while ((jerr = json_tokener_get_error(tok)) == json_tokener_continue) {
        stringlen = strlen(json);
        *responses = json_tokener_parse_ex(tok, json, stringlen);
    }
    if (jerr != json_tokener_success) {
        fprintf(stderr, "JSON Error: %s\n", json_tokener_error_desc(jerr));
        return 1;
    }
    json_tokener_free(tok);
    return 0;
}

char *mx_parse_str(char *jstr, char buf) {
    int len = mx_strlen(jstr) + 1;
    char *tmp = mx_strnew(len);

    for (int i = 0; jstr[i]; i++)
        tmp[i] = jstr[i];
    tmp[len - 1] = buf;
    if (malloc_size(jstr))
        mx_strdel(&jstr);
    jstr = mx_strdup(tmp);
    if (malloc_size(tmp))
        mx_strdel(&tmp);
    return jstr;
}

void mx_sign_up(struct json_object *jobj) {
    t_event event;
    struct json_object *nick;
    struct json_object *password;
    struct json_object *login;

    event.log_in = (t_log_in *)malloc(sizeof(t_log_in));
    json_object_object_get_ex(jobj, "login", &login);
    json_object_object_get_ex(jobj, "password", &password);
    json_object_object_get_ex(jobj, "nick", &nick);

    event.log_in->login = json_object_get_string(login);
    event.log_in->nick = json_object_get_string(nick);
    event.log_in->password = json_object_get_string(password);

    printf("=====================================================\n");
    printf("LOGIN = %s\n", event.log_in->login);
    printf("NICK = %s\n", event.log_in->nick);
    printf("PASSWORD = %s\n", event.log_in->password);
    printf("=====================================================\n");
}

static void* ws_establishconnection(void *vsock) {
    int sock = (int)(intptr_t)vsock;  /* File descriptor.               */
    int n;                           /* Number of bytes sent/received. */
    char buf;
    char *jstr = mx_strnew(0);
    struct json_object *jobj = json_object_new_object();
    struct json_object *event;
    char *events[] = {"sign_up", "sign_in"};



    while ((n = read(sock, &buf, 1)) > 0) {
        jstr = mx_parse_str(jstr, buf);
        if (jstr[mx_strlen(jstr) - 1] == '}') {
            printf("jstr = %s\n", jstr);

            if (parse_json((const char *)jstr, &jobj))
                mx_printerr("Failed to parse JSON responses.\n");
            printf("JSON = %s\n", json_object_to_json_string(jobj));

            //JSON OBJ GET
            json_object_object_get_ex(jobj, "event", &event);
            printf("%s\n", json_object_get_string(event));
            if (strcmp(json_object_get_string(event), events[0]) == 0)
                mx_sign_up(jobj);
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
