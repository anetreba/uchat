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
    int id;
    char *login;
    char *nick;
    char *password;
    char *email;
    int argc;
    char **colname;
    int tokens;
    int verify_code;
}               t_data;

typedef struct s_signup {
    int status;
    int verify_code;
}               t_signup;

typedef struct s_send_message {
    int id_sender;
    const char *message;
    int type;
    int group;
}               t_send_message;

typedef struct s_renew {
    int id;
    const char *auth_token;
}               t_renew;

typedef struct s_renrooms {
    int room_id;
    const char *room_name;
}               t_renrooms;

typedef struct s_event {
    int server_sock;
    int *client_socks;
    int new_open_socket;
    t_log_in *log_in;
    t_send_message *send_message;
    t_renew *renew;
    t_renrooms *renrooms;
}              t_event;

typedef struct s_response {
    int id;
    int status;
    char *auth_token;
    int tokens;
}               t_response;

void mx_valid_event(struct json_object *jobj, t_event *event);
int mx_init_sqli(char *sql, int (*callback)(void *, int, char **, char **), void *data);
void mx_server_socket(int port);
void mx_printerr(char *str);
char *mx_parse_str(char *jstr, char buf);
int parse_json(const char *json, json_object **responses);
void mx_renew(struct json_object *jobj, t_event *event);
void mx_shuffle(void *array, size_t n, size_t size);

//models
void mx_model_insert (char *table, char *rows, char *vals);
int mx_model_select(const char *search, char *tables,
                    int (*callback)(void *, int, char **, char **),
                    void *data);
void mx_model_update(char *table, char *str, char *condition);
void mx_model_del(char *table, char *condition);


//controllers
t_signup mx_contr_signup(t_log_in *user);
t_response *mx_contr_signin(t_log_in *user);
t_list mx_contr_renew(t_renew *tok);
char *mx_gen_auth_token(int len);
int mx_date_now();
int mx_date_aval(int time);
void mx_return_renew_json(t_list *resp, int sock);
void mx_return_signup_json(t_signup status, int sock);
int mx_gen_verify_code();
int mx_sendmail(const char *to, const char *from, const char *subject, const char *message);
void mx_verify_mail(char *login);
void mx_renew_rooms(struct json_object *jobj, t_event *event);
t_list mx_contr_renew_rooms(t_renew *tok);

#endif
