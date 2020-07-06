#include "header.h"

int mx_date_convertor(int date) {
    struct tm tm;

    if (date == 0)
        date = mx_date_now();
    time_t epoch;
    if (strptime(timestamp, "%Y-%m-%d %H:%M:%S", &tm) != NULL)
        epoch = mktime(&tm);
    else
}