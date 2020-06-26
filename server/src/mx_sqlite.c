#include "header.h"

void mx_init_sqli(char *sql, int (*callback)(void *, int, char **, char **), void *data) {
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("./src/db/server.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    rc = sqlite3_exec(db, sql, callback, data, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return;
    }
    sqlite3_close(db);
}
