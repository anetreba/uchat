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

////////////////////FOR RENDER MESSAGE AND ROOMS/////////////////////

typedef struct s_mess {
    char *message;
    int sender_id;
    char *sender_nick;
    int date_send;
    int type;

    GtkWidget *row_user;
    GtkWidget *row_msg;
    GtkWidget *message_button;
    GtkWidget *user_button;

}               t_mess;

typedef struct s_list_room {
    int room_id;
    char *room_name;
    t_list *mess;

    GtkWidget *row;
    GtkWidget *room_btn;
    GtkWidget *list_box;
}               t_list_room;


////////////////////////////////////////////////////////////////////

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
    GtkWidget *list_rooms;
    GtkWidget *new_room;
    GtkWidget *row_user; /////
    GtkWidget *row_msg;
    GtkWidget *message_button;
    GtkWidget *user_button; ////
    GtkWidget *scrolled_window;
    GtkWidget *viewport;
    GtkWidget *msg;
    GtkWidget *contacts;
    GtkWidget *contacts_wdw;
    GtkWidget *contacts_scrolled_wdw;
    GtkWidget *contacts_listbox;
    GtkWidget *new_contact_btn;
    GtkWidget *contacts_back_btn;
    GtkWidget *new_room_btn;
    GtkWidget *groups_wdw;
    GtkBuilder *builder4;
    GtkBuilder *builder5;
    GtkBuilder *add_cont_builder;
    GtkWidget *add_contact_wdw;
    GtkWidget *add_contact_confirm_btn;
    GtkWidget *add_contact_entry_field;
    GtkWidget *add_contact_back_btn;
    GtkWidget *add_room_confirm_btn;
    GtkWidget *add_room_entry_field;
    GtkWidget *add_room_back_btn;
    GtkWidget *users_listbox;
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
    int status;
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
}               t_log_in;

typedef struct s_sign_up {
    const char *login;
    const char *password;
    const char *nick;
    const char *email;
}               t_sign_up;

typedef struct s_send_message {
    int sender_id;
    const char *message;
    char *nick;
    int type;
    int room_id;
    int date_send;
    int tokens;
}               t_send_message;

typedef struct s_renew_contacts {
    int contact_id;
    char *nickname;

    GtkWidget *row;
    GtkWidget *cont_btn;
}               t_renew_contacts;

typedef struct s_del_room {
    int user_id;
    int room_id;
}               t_del_room;

typedef struct s_add_contact {
    int sender_id;
    int contact_id;
    const char *nick;
}               t_add_contact;

typedef struct s_cont {
    char *nick;
    int id;
}               t_cont;

typedef struct s_info_room {
    char *room_name;
    t_list *cont;
}               t_info_room;

typedef struct s_cont_for_add_room {
    int id;
    char *nick;

    GtkWidget *row;
    GtkWidget *cont_btn;
}               t_cont_for_add_room;

typedef struct s_event {
    int network_socket;
    int prev_room_id;
    int status;
    t_gtk *gtk;
    t_send_message *send_message;
    t_log_in *log_in;
    t_sign_up *sign_up;
    t_data *data;
    t_list *renew;
    t_list *list_room;
    t_renew_contacts *renew_contacts;
    t_del_room *del_room;
    t_add_contact *add_contact;
    t_list *list_contact;
    t_info_room *info_room;
    t_list *for_new_room;
}              t_event;

typedef struct s_response {
    int id;
    int status;
    char *auth_token;
    int tokens;
}               t_response;

void *mx_client_recv(void *data);
gboolean mx_show_new_contact(void *data);
void mx_show_groups_wdw(GtkButton *button, t_event *event);
gboolean mx_show_in_cont(void *data);
gboolean mx_show_label_no_user(void *data);
gboolean mx_render_cont(void *data);
gboolean mx_render_cont_list(void *data);

void mx_contr_select_contacts(t_event *event);
void show_contacts_wdw(GtkButton *button, t_event *event);

void mx_listroom_and_mess(t_event *event);
gboolean mx_parse_room_front(void *data);
void chat_window(t_event *event);
gboolean mx_show_chat_window(void *data);
gboolean show_error_label(void *data);

void create_row(t_event *event);
void mx_add_new_message(t_event *event, GtkWidget *msg);
void new_room(GtkButton *button, t_event *event);
void send_messages(GtkButton *button, t_event *event);

void mx_valid_event(struct json_object *jobj, t_event *event);
//crud
void mx_model_update(char *table, char *str, char *condition);
void mx_model_insert (char *table, char *rows, char *vals);
int mx_model_select(const char *search, char *tables,
                    int (*callback)(void *, int, char **, char **),
                    void *data);
int mx_init_sqli(char *sql, int (*callback)(void *, int, char **, char **), void *data);

int mx_init_sqli(char *sql, int (*callback)(void *, int, char **, char **), void *data);
void mx_server_socket(int port);
void mx_printerr(char *str);
char *mx_parse_str(char *jstr, char buf);
int parse_json(const char *json, json_object **responses);
t_response *mx_model_logined(t_data *data);
void json_parse(json_object *jobj, t_list *lst);
void *mx_model_new_message(t_send_message *data);
void mx_model_renew_contacts(json_object *obj);
void *mx_model_add_contact(t_add_contact *data);

void mx_json_read(t_event *event);
//controllers
void mx_contr_auth(t_event *event, json_object *jobj);
void mx_contr_renew(t_event *event, json_object *jobj);
void mx_contr_update_rooms(json_object *jobj, t_event *event);
void mx_contr_new_message(t_event *event, json_object *jobj);
void mx_contr_renew_contacts(t_event *event);
void mx_json(t_event *event, char *action);
void mx_contr_add_contact(t_event *event, json_object *jobj);


void json_parse_cont(json_object *jobj, t_list *lst);

#endif
