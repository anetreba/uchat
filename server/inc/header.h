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

#include <sqlite3.h>
#include <../src/json/json.h>
#include "../libmx/inc/libmx.h"

void mx_init_sqli();
void mx_server_socket(int port);
void mx_printerr(char *str);

#endif
