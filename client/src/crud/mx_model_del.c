#include "header.h"

void mx_model_del(char *table, char *condition) {
    char *sql;

    asprintf(&sql, "DELETE FROM %s WHERE %s;", table, condition);
    mx_init_sqli(sql, 0, 0);
    free(sql);
}
