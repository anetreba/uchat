#include "header.h"

//static t_response *create_response(char *str, int tok) {
//    t_response *resp = (t_response *)malloc(sizeof(t_response));
//    memset(resp, 0, sizeof(t_response));
//
//    if(str) {
//        resp->auth_token = mx_strdup(str);
//        resp->status = 0;
//        resp->tokens = tok;
//    }
//    else
//        resp->status = 1;
//    return resp;
//}



t_response *mx_model_logined(t_data *data) {
    char *vals;
    char *str = NULL;

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
    return 0;
}
