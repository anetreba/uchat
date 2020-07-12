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
#include <gtk/gtk.h>
#include <ctype.h>

typedef struct s_gtk {
    GtkBuilder *builder;
    GtkBuilder *builder2;
    GtkWidget *window;
    GtkWidget *fixed;
    GtkWidget *sign_in_btn;
    GtkWidget *sign_up_btn;
    GtkWidget *new_nickname;
    GtkWidget *new_login;
    GtkWidget *reg_window;
    GtkWidget *new_password;
    GtkWidget *new_email;
    GtkWidget *reg_btn;
    GtkWidget *back_btn;
}               t_gtk;

typedef struct s_log_in {
    const char *login;
    const char *password;
//    const char *nick;
}               t_log_in;

typedef struct s_sign_up {
    const char *login;
    const char *password;
    const char *nick;
    const char *email;
}               t_sign_up;

typedef struct s_send_message {
    int id_sender;
    const char *message;
    int type;
    int group;
}               t_send_message;

typedef struct s_event {
    int network_socket;
    t_gtk *gtk;
    t_send_message *send_message;
    t_log_in *log_in;
    t_sign_up *sign_up;
}              t_event;

void mx_valid_event(struct json_object *jobj, int sock);
int mx_init_sqli(char *sql, int (*callback)(void *, int, char **, char **), void *data);
void mx_server_socket(int port);
void mx_printerr(char *str);
char *mx_parse_str(char *jstr, char buf);
int parse_json(const char *json, json_object **responses);


#endif