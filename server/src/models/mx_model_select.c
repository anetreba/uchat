#include "header.h"

void mx_model_select(char *search, char *tables,
                     int (*callback)(void *, int, char **, char **),
                     void *data) {
    char *sql;

    asprintf(&sql, "SELECT %s FROM %s", search, tables);
    mx_sqlite(sql, callback, data);
    free(sql);
}