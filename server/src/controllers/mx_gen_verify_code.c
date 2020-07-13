#include "header.h"

int mx_gen_verify_code(int digits) {
    int r;

    srand(digits);
    r = rand();
    return r;
}
