#include "header.h"

void mx_crate_table(char *table, char *rows, char *vals) {
    char *sql;

    asprintf(&sql, "INSERT INTO %s (%s) VALUES (%s);", table,
             rows, vals);
    printf("SQL QUERY: %s\n", sql);
    mx_init_sqli(sql, 0, 0);
    free(sql);
}
