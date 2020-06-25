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
#include <../src/json-c/json.h>
#include <malloc/malloc.h>


void mx_printerr(char *str);

typedef struct s_log_in {
    const char *login;
    const char *password;
    const char *nick;
}               t_log_in;

typedef struct s_send_message {
    int id_sender;
    char *message;
    int type;
    int id_receiver;
}               t_send_message;

typedef struct s_event {
    t_log_in *log_in;
    t_send_message *t_send_message;
}              t_event;

#endif
