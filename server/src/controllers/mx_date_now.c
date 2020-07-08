#include "header.h"

int mx_date_now() {
    time_t rawtime;
    struct tm *timeinfo;

    time (&rawtime);
    timeinfo = localtime(&rawtime);
    return mktime(timeinfo);
}
