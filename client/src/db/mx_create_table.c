#include "uchat.h"

void mx_table_contacts(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'Contacts'(" \
        "id             INTEGER PRIMARY KEY AUTOINCREMENT," \
        "nick           VARCHAR(50)     NOT NULL," \
        "user_id        INTEGER
    mx_create_table(db, sql, mx_callback);
}


void mx_create_table(sqlite3 *db, char *sql,
                       int (*callback)(void*, int, char**, char**)) {
    int connection_point;

    connection_point = sqlite3_exec(db, sql, callback, NULL, NULL);
    if (connection_point != SQLITE_OK)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
}

void mx_db_creation(sqlite3 **db) {
    int rs;
    char sql[512];

    rs = sqlite3_open("uchat.db", db);
    if(connection_point)
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
    else
        printf(stdout, "DATABASE succesfully connected\n");
    sprintf(sql, "DROP TABLE IF EXISTS ACTIVITY;");

    mx_create_table(*db, sql, mx_callback);
    mx_table_contacts(*db, sql);
    mx_cre
}