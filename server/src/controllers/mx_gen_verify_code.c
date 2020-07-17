#include "header.h"

int mx_gen_verify_code(int digits) {
    int arr[] = {0,1,2,3,4,5,6,7,8,9};
    int r = 0;

    srand(time(NULL));
    mx_shuffle(arr, 10, sizeof(int));
    for (int i = 0; i < digits; i++)
        r = r * 10 + arr[i + 1];
    return r;
}
