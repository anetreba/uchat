#include "header.h"

void mx_contr_logout () {
    char *vals;
    char *str = NULL;

    asprintf(&vals, "setting = '%s'", "auth_token");
    asprintf(&str, "value ='%s'", "");
    mx_model_update("Settings", str, vals);
    free(vals);
    asprintf(&vals, "setting = '%s'", "user_id");
    asprintf(&str, "value ='%d'", 0);
    mx_model_update("Settings", str, vals);
    free(vals);
    asprintf(&vals, "setting = '%s'", "tokens");
    asprintf(&str, "value ='%d'", 0);
    mx_model_update("Settings", str, vals);
    free(vals);
}
