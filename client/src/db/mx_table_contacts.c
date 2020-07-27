#include "header.h"

void mx_table_contacts(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'Contacts'(" \
        "id             INTEGER PRIMARY KEY AUTOINCREMENT," \
        "nick           VARCHAR(50)     NOT NULL," \
        "user_id        INTEGER");
    mx_create_table(db, sql, mx_callback);
}
