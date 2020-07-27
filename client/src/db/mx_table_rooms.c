#include "header.h"

void mx_table_rooms(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'Rooms'(" \
        "id             INTEGER PRIMARY KEY AUTOINCREMENT," \
        "room_name      VARCHAR(50) NOT NULL, " \
        "room_id        INTEGER");
    mx_create_table(db, sql, mx_callback);
}
