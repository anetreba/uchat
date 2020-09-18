#include "header.h"

int mx_callback(void *data, int argc, char **argv, char **ColName) {
    (void)data;
    (void)argc;
    (void)argv;
    (void)ColName;
    return 0;
}

void mx_db_creation() {
    int rs;
    char sql[512];
    sqlite3 *db;

    rs = sqlite3_open("./src/db/client.db", &db);
    if (rs)
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    else
        fprintf(stdout, "DATABASE succesfully connected\n");
    sprintf(sql, "DROP TABLE IF EXISTS ACTIVITY;");
    mx_create_table(db, sql, mx_callback);
    mx_table_contacts(db, sql);
    mx_table_messages(db, sql);
    mx_table_rooms(db, sql);

    mx_init_sqli(sql, 0, 0);
}
