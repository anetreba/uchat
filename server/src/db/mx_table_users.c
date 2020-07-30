#include "header.h"

void mx_table_users(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'Users'(" \
        "id             INTEGER PRIMARY KEY AUTOINCREMENT," \
        "user_id        INTEGER," \
        "contact_id     INTEGER," \
        "nick           INTEGER)");
    mx_create_table(db, sql, mx_callback);
}
