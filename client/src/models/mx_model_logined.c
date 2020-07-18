#include "header.h"

t_response *mx_model_logined(t_data *data) {
    char *vals;
    char *str = NULL;
    if (data) {
        asprintf(&vals, "setting = '%s'", "auth_token");
        asprintf(&str, "value ='%s'", data->auth_token);
        mx_model_update("Settings", str, vals);
        free(vals);
        asprintf(&vals, "setting = '%s'", "user_id");
        asprintf(&str, "value ='%d'", data->id);
        mx_model_update("Settings", str, vals);
        free(vals);
        asprintf(&vals, "setting = '%s'", "tokens");
        asprintf(&str, "value ='%d'", data->tokens);
        mx_model_update("Settings", str, vals);
        free(vals);
    }
    return 0;
}
