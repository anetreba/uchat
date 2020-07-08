#include "header.h"

static int intN(int n) {
    return rand() % n;
}

char *mx_gen_auth_token(int len) {
    char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char *rstr = malloc((len + 1) * sizeof(char));

    for (int i = 0; i < len; i++) {
        rstr[i] = alphabet[intN(strlen(alphabet))];
    }
    rstr[len] = '\0';
    return rstr;
}
