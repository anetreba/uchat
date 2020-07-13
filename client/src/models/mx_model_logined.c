#include "header.h"

static t_response *create_response(char *str, int tok) {
    t_response *resp = (t_response *)malloc(sizeof(t_response));
    memset(resp, 0, sizeof(t_response));

    if(str) {
        resp->auth_token = mx_strdup(str);
        resp->status = 0;
        resp->tokens = tok;
    }
    else
        resp->status = 1;
    return resp;
}

t_response *mx_contr_logined(const char *resp) {
    char *vals;
    char *str;
    char *auth_token = NULL;
    t_data data;
    int rs;

    asprintf(&vals, "Users WHERE login = '%s'", user->login);
    rs = mx_model_select("login,pass,tokens", vals, callback_signin, &data);
    if (data.login != NULL && data.password != NULL &&
        mx_strcmp(user->login, data.login) == 0 &&
        mx_strcmp(user->password, data.password) == 0) {
        auth_token = mx_gen_auth_token(24);

        asprintf(&vals, "login = '%s'", user->login);
        asprintf(&str, "auth_token='%s', token_aval='%u'", auth_token, mx_date_aval(864000));
        mx_model_update("Users", str, vals);
    }
    free(vals);
    return create_response(auth_token, data.tokens);
}
