#include "header.h"

int mx_model_select(const char *search, char *tables,
                     int (*callback)(void *, int, char **, char **),
                     void *data) {
    char *sql;

    asprintf(&sql, "SELECT %s FROM %s", search, tables);
    if (mx_init_sqli(sql, callback, data) == 0)
        return 0;
    free(sql);
    return 1;
}
