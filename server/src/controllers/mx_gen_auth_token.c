#include "header.h"

void mx_shuffle(void *array, size_t n, size_t size) {
    char tmp[size];
    char *arr = array;
    size_t stride = size * sizeof(char);

    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; ++i) {
            size_t rnd = (size_t) rand();
            size_t j = i + rnd / (RAND_MAX / (n - i) + 1);

            memcpy(tmp, arr + j * stride, size);
            memcpy(arr + j * stride, arr + i * stride, size);
            memcpy(arr + i * stride, tmp, size);
        }
    }
}

char *mx_gen_auth_token(int len) {
    char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char *rstr = malloc((len + 1) * sizeof(char));

    srand(time(NULL));
    mx_shuffle(alphabet, 62, sizeof(char));

    for (int i = 0; i < len; i++)
        rstr[i] = alphabet[i];
    rstr[len] = '\0';
    return rstr;
}
