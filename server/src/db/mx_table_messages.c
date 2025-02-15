#include "header.h"

void mx_table_messages(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'Messages' (" \
        "id             INTEGER PRIMARY KEY AUTOINCREMENT," \
        "message        TEXT," \
        "sender_id      INTEGER," \
        "room_id        INTEGER," \
        "recieve_status INTEGER," \
        "date_send      INTEGER," \
        "type           INTEGER)");
    mx_create_table(db, sql, mx_callback);
}
