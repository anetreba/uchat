#include "header.h"

static t_response *create_response(char *str, int tok, int id) {
    t_response *resp = (t_response *)malloc(sizeof(t_response));
    memset(resp, 0, sizeof(t_response));

    if(str) {
        resp->id = id;
        resp->auth_token = mx_strdup(str);
        resp->status = 0;
        resp->tokens = tok;
    }
    else
        resp->status = 1;
    return resp;
}

static int callback_signin(void *data, int argc, char **argv, char **ColName) {
    t_data *udata = (t_data *)data;
    ColName = NULL;

    if (argc > 0 && argv) {
        udata->id = atoi(argv[0]);
        udata->login = strdup(argv[1]);
        udata->password = strdup(argv[2]);
        udata->tokens = atoi(argv[3]);

    }
    return 0;
}

t_response *mx_contr_signin(t_log_in *user) {
    char *vals;
    char *str;
    char *auth_token = NULL;
    t_data data;
    int rs;

    asprintf(&vals, "Users WHERE login = '%s'", user->login);
    rs = mx_model_select("id,login,pass,tokens", vals, callback_signin, &data);
    if (data.login != NULL && data.password != NULL &&
        mx_strcmp(user->login, data.login) == 0 &&
        mx_strcmp(user->password, data.password) == 0) {
        auth_token = mx_gen_auth_token(24);

        asprintf(&vals, "login = '%s'", user->login);
        asprintf(&str, "auth_token='%s', token_aval='%u'", auth_token, mx_date_aval(864000));
        mx_model_update("Users", str, vals);
    }
    free(vals);
    return create_response(auth_token, data.tokens, data.id);
}
