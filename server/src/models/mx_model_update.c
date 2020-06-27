#include "header.h"

void mx_model_update(char *table, char *str, char *condition) {
    char *sql;

    asprintf(&sql, "UPDATE %s SET %s WHERE %s;", table, str, condition);
    mx_init_sqli(sql, 0, 0);
    free(sql);
}
