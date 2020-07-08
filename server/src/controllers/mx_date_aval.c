#include "header.h"

int mx_date_aval(int time) {
    int date_now;

    date_now = mx_date_now();
    return date_now + time;
}
