#include "header.h"

void mx_table_usersmeta(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'UsersMeta'(" \
        "id             INTEGER PRIMARY KEY AUTOINCREMENT," \
        "login          VARCHAR(50)," \
        "nick           VARCHAR(50)," \
        "auth_token     VARCHAR(255)," \
        "token_aval     TIMESTAMP," \
        "tokens         INTEGER," \
        "email          VARCHAR(50)," \
        "verify_code    INTEGER," \
        "activated      INTEGER," \
        "sock           INTEGER)");
    mx_create_table(db, sql, mx_callback);
}
