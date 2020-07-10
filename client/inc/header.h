#ifndef HEADER_H
#define HEADER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>
#include <arpa/inet.h>
#include <../json-c/inc/json.h>
#include <malloc/malloc.h>
#include "../libmx/inc/libmx.h"

#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
// #include <string.h>
#include <gtk/gtk.h>
// #include <gtk/gtkx.h>
// #include <math.h>
#include <ctype.h>


typedef struct s_log_in {
    const char *login;
    const char *password;
    const char *nick;
}               t_log_in;

typedef struct s_send_message {
    int id_sender;
    const char *message;
    int type;
    int group;
}               t_send_message;

typedef struct s_event {
    t_log_in *log_in;
    t_send_message *send_message;
}              t_event;

void mx_valid_event(struct json_object *jobj, int sock);
int mx_init_sqli(char *sql, int (*callback)(void *, int, char **, char **), void *data);
void mx_server_socket(int port);
void mx_printerr(char *str);
char *mx_parse_str(char *jstr, char buf);
int parse_json(const char *json, json_object **responses);


#endif
