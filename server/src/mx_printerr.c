#include "header.h"

void mx_printerr(char *str) {
	write(2, str, strlen(str));
}
