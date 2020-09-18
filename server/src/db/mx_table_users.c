#include "header.h"

void mx_table_users(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'Users' (" \
        "id             INTEGER PRIMARY KEY AUTOINCREMENT," \
        "user_id        INTEGER," \
        "login          VARCHAR(50)," \
        "pass           VARCHAR(100)," \
        "tokens         INTEGER," \
        "sock           INTEGER," \
        "email          VARCHAR(50)," \
        "last_online    TIMESTAMP," \
        "verify_code    INTEGER," \
        "activated      INTEGER," \
        "auth_token     VARCHAR(255)," \
        "token_aval     TIMESTAMP," \
        "nick           INTEGER)");
    mx_create_table(db, sql, mx_callback);
}
