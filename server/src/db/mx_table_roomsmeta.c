#include "header.h"

void mx_table_roomsmeta(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'RoomsMeta'(" \
        "id             INTEGER PRIMARY KEY AUTOINCREMENT," \
        "room_id        INTEGER," \
        "user_id        INTEGER," \
        "room_name      VARCHAR(50) NOT NULL)");
    mx_create_table(db, sql, mx_callback);
}
