#include "header.h"

static t_response *create_response(char *str) {
    int status = 1;
    t_response *resp = (t_response *)malloc(sizeof(t_response));

    if(str) {
        resp->status = 0;
    }
    resp->auth_token = str;
    resp->status = status;
    return resp;
}

static int callback_signin(void *data, int argc, char **argv, char **ColName) {
    t_data *udata = (t_data *)data;
    ColName = NULL;

    if (argc > 0 && argv) {
        udata->login = strdup(argv[0]);
        udata->password = strdup(argv[1]);
    }
    return 0;
}

t_response *mx_contr_signin(t_log_in *user) {
    char *vals;
    char *str;
    char *auth_token;
    t_data data;
    int rs;

    asprintf(&vals, "Users WHERE login = '%s'", user->login);
    rs = mx_model_select("login,pass", vals, callback_signin, &data);
    if (mx_strcmp(user->login, data.login) == 0 &&
        mx_strcmp(user->password, data.password) == 0) {
        auth_token = mx_gen_auth_token(24);

        printf("***********************************\n");
        printf("Auth_Token: %s\n", auth_token);
        printf("***********************************\n");

        asprintf(&vals, "login = '%s'", user->login);
        asprintf(&str, "auth_token = '%s'", auth_token);
        mx_model_update("Users", str, vals);
        return create_response(auth_token);
    }
    free(vals);
    return 0;
}
