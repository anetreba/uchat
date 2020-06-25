#include "header.h"

void mx_model_insert (char *table, char *rows, char *vals) {
    char *sql;

    asprintf(&sql, "INSERT INTO %s (%s) VALUES (%s);", table,
             rows, vals);
    mx_sqlite(sql, 0, 0);
    free(sql);
}
