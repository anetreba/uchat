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
#include <sqlite3.h>

typedef struct s_gtk {
    GtkBuilder *builder;
    GtkBuilder *builder2;
    GtkBuilder *builder3;
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
    GtkWidget *chat_entry_message;
    GtkWidget *chat_messages_box1;
    GtkWidget *chat_send_btn;
    GtkWidget *chat_window;
    GtkWidget *list_box;
    GtkWidget *test_label;
}               t_gtk;

typedef struct s_data {
    int id;
    int status;
    char *login;
    char *nick;
    char *password;
    char *name_room;
    char *email;
    char **colname;
    int tokens;
    int verify_code;
    const char *auth_token;
}               t_data;

typedef struct s_renew {
    int room_id;
    char *name_room;
    char *message;
    int sender_id;
    int date_send;
    int recieve_status;
}               t_renew;

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
    t_data *data;
}              t_event;

typedef struct s_response {
    int id;
    int status;
    char *auth_token;
    int tokens;
}               t_response;

//crud
void mx_model_update(char *table, char *str, char *condition);
void mx_model_insert (char *table, char *rows, char *vals);
int mx_model_select(const char *search, char *tables,
                    int (*callback)(void *, int, char **, char **),
                    void *data);
int mx_init_sqli(char *sql, int (*callback)(void *, int, char **, char **), void *data);

void mx_valid_event(struct json_object *jobj, int sock);
int mx_init_sqli(char *sql, int (*callback)(void *, int, char **, char **), void *data);
void mx_server_socket(int port);
void mx_printerr(char *str);
char *mx_parse_str(char *jstr, char buf);
int parse_json(const char *json, json_object **responses);
t_response *mx_model_logined(t_data *data);
void json_parse(json_object *jobj, t_list *lst);
int mx_update_rooms(t_list *lst);


//controllers
void mx_contr_auth(t_event *event, json_object *jobj);
void mx_contr_renew(t_event *event);

#endif
