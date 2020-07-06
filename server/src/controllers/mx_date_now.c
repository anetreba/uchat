#include "header.h"

int mx_date_now() {
    time_t rawtime;
    struct tm *timeinfo;

    time (&rawtime);
    timeinfo = localtime(&rawtime);
    //printf ( "Current local time and date: %u", mktime(timeinfo) );
    return mktime(timeinfo);
}
