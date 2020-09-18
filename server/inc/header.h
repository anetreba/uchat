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
#include <sys/stat.h>
#include <sys/types.h>

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
    int admin_id;
    char *auth_token;
    int sock;
    int res;
}               t_data;

typedef struct s_signup {
    int status;
    int verify_code;
}               t_signup;

typedef struct s_send_message {
    int sender_id;
    int room_id;
    int type;
    int date_send;
    int tokens;
    const char *auth_token;
    const char *message;
}               t_send_message;

typedef struct s_renew {
    int id;
    const char *auth_token;
}               t_renew;

typedef struct s_renew_rooms {
    int room_id;
    const char *room_name;
    const char *auth_token;
}               t_renew_rooms;

typedef struct s_renew_contacts {
    int user_id;
    int contact_id;
    char *nickname;
    const char *auth_token;
}               t_renew_contacts;

typedef struct s_edit_room {
    int room_id;
    int room_name;
    int sock;
    int user_id;
    const char *auth_token;
}               t_edit_room;

typedef struct s_add_contact {
    int id;
    const char *nick;
    int sender_id;
    int status;
    const char *auth_token;
}               t_add_contact;


typedef struct s_info_room {
    int room_id;
    char *room_name;
    int users_count;
    int *cont_id;
    int sender_id;
    char *auth_token;
}               t_info_room;

typedef struct s_sock {
    int sock;
}               t_sock;

typedef struct s_event {
    int server_sock;
    int *client_socks;
    int new_open_socket;
    t_log_in *log_in;
    t_send_message *send_message;
    t_renew *renew;
    t_renew_rooms *renew_rooms;
    t_renew_contacts *renew_contacts;
    t_edit_room *edit_room;
    t_add_contact *add_contact;
    t_info_room *add_room;
    t_list *sock;
}               t_event;

typedef struct s_response {
    int id;
    int status;
    int room_id;
    int sender_id;
    int contact_id;
    char *nick;
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
void mx_add_room(struct json_object *jobj, t_event *event);

//models
void mx_model_insert (char *table, char *rows, char *vals);
int mx_model_select(const char *search, char *tables,
                    int (*callback)(void *, int, char **, char **),
                    void *data);
void mx_model_update(char *table, char *str, char *condition);
void mx_model_del(char *table, char *condition);
void mx_demonize();


//controllers
t_signup mx_contr_signup(t_log_in *user);
t_response *mx_contr_signin(t_event *event);
t_list *mx_contr_renew(t_renew *tok);
char *mx_gen_auth_token(int len);
int mx_date_now();
int mx_date_aval(int time);
void mx_return_renew_json(t_list *resp, int sock);
void mx_return_signup_json(t_signup status, int sock);
int mx_gen_verify_code();
int mx_sendmail(const char *to, const char *from, const char *subject, const char *message);
void mx_verify_mail(char *login);
void mx_renew_rooms(struct json_object *jobj, t_event *event);
t_list *mx_contr_renew_rooms(t_renew_rooms *tok);
t_list *mx_recieve_mess(t_send_message *mess);
t_list *mx_contr_renew_contacts(t_renew_contacts *tok);
t_list *mx_contr_renew_contacts(t_renew_contacts *tok);
void mx_return_renew_contacts_json(t_list *resp, int sock);
void *mx_contr_del_room(t_edit_room *room);
t_data *mx_contr_add_contact(t_add_contact *tok);
t_event *mx_contr_add_new_room(t_event *event);
void mx_add_room_resp(t_event *event);

//create_db
void mx_db_creation();
int mx_callback(void *data, int argc, char **argv, char **ColName);
void mx_create_table(sqlite3 *db, char *sql,
                     int (*callback)(void*, int, char**, char**));
void mx_table_messages(sqlite3 *db, char *sql);
void mx_table_rooms(sqlite3 *db, char *sql);
void mx_table_roomsmeta(sqlite3 *db, char *sql);
void mx_table_users(sqlite3 *db, char *sql);
void mx_table_usersmeta(sqlite3 *db, char *sql);
#endif
