#include "header.h"

void mx_set_value(char *table, char *str, char *condition) {
    char *sql;

    asprintf(&sql, "UPDATE %s SET %s WHERE %s;", table, str, condition);
    mx_sqlite(sql, 0, 0);
    free(sql);
}