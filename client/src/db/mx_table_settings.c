#include "header.h"

void mx_table_settings(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'Settings'(" \
        "id           INTEGER PRIMARY KEY AUTOINCREMENT," \
        "setting      VARCHAR(255) NOT NULL, " \
        "value        TEXT");
    mx_create_table(db, sql, mx_callback);
}
