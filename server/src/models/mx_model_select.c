#include "header.h"

int mx_model_select(const char *search, char *tables,
                     int (*callback)(void *, int, char **, char **),
                     void *data) {
    char *sql;
    char rs;

    asprintf(&sql, "SELECT %s FROM %s", search, tables);
    printf("SQL: %s\n", sql);
    rs = mx_init_sqli(sql, callback, data);
    if ( rs == 0)
        return 0;
    free(sql);
    return 1;
}
