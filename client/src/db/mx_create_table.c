#include "header.h"

void mx_create_table(sqlite3 db, char *sql,
                     int (*callback)(void*, int, char**, char**)) {
    int connection_point;

    connection_point = sqlite3_exec(db, sql, callback, NULL, NULL);
    if (connection_point != SQLITE_OK)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
}
