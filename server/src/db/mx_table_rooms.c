#include "header.h"

void mx_table_rooms(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'Rooms'(" \
        "id             INTEGER PRIMARY KEY AUTOINCREMENT," \
        "user_id        INTEGER" \
        "room_id        INTEGER, " \
        "message_id     INTEGER, " \
        "room_name      VARCHAR(50) NOT NULL)");
    mx_create_table(db, sql, mx_callback);
}
