#ifndef HEADER_H
#define HEADER_H

#define MAX_CLIENTS 8

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
#include <time.h>

#include <sqlite3.h>
#include "../json-c/inc/json.h"
#include "../libmx/inc/libmx.h"

typedef struct s_log_in {
    const char *login;
    const char *password;
    const char *nick;
    const char *email;
}               t_log_in;

typedef struct s_upd {
    char *message;
    int room_id;
    char *room_name;
    int sender_id;
    int date_send;
    int recieve_status;
}               t_upd;

typedef struct s_data {
    char *login;
    char *nick;
    char *password;
    char *email;
    int argc;
    char **colname;
}               t_data;

typedef struct s_send_message {
    int id_sender;
    const char *message;
    int type;
    int group;
}               t_send_message;

typedef struct s_renew {
    const char *auth_token;
}               t_renew;

typedef struct s_event {
    t_log_in *log_in;
    t_send_message *send_message;
    t_renew *renew;
}              t_event;

typedef struct s_response {
    int status;
    char *auth_token;
}               t_response;

void mx_valid_event(struct json_object *jobj, int sock);
int mx_init_sqli(char *sql, int (*callback)(void *, int, char **, char **), void *data);
void mx_server_socket(int port);
void mx_printerr(char *str);
char *mx_parse_str(char *jstr, char buf);
int parse_json(const char *json, json_object **responses);
void mx_renew(struct json_object *jobj, int sock);


//models
void mx_model_insert (char *table, char *rows, char *vals);
int mx_model_select(const char *search, char *tables,
                    int (*callback)(void *, int, char **, char **),
                    void *data);
void mx_model_update(char *table, char *str, char *condition);
void mx_model_del(char *table, char *condition);


//controllers
int mx_contr_signup(t_log_in *user);
t_response *mx_contr_signin(t_log_in *user);
t_list mx_contr_renew(t_renew *tok);
char *mx_gen_auth_token(int len);
int mx_date_now();
int mx_date_aval(int time);
void mx_return_renew_json(t_list *resp, int sock);


#endif
