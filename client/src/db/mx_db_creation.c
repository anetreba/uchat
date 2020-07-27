#include "header.h"

void mx_db_creation() {
    int rs;
    char sql[512];

    rs = sqlite3_open("uchat.db", db);
    if(rs)
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
    else
        printf(stdout, "DATABASE succesfully connected\n");
    sprintf(sql, "DROP TABLE IF EXISTS ACTIVITY;");
    mx_create_table(*db, sql, mx_callback);
    mx_table_contacts(*db, sql);
    mx_table_messages(*db, sql);
    mx_table_rooms(*db, sql);

    mx_init_sqli(sql, 0, 0);
}