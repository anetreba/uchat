#include "header.h"

static int callback_renew(void *data, int argc, char **argv, char **ColName) {
    t_data *udata = (t_data *)data;
    ColName = NULL;

    if (argc > 0 && argv) {
        udata->login = strdup(argv[0]);
        udata->password = strdup(argv[1]);
    }
    return 0;
}

t_response mx_contr_renew(t_renew *tok) {
    char *vals;
    char *str;
    char *auth_token;
    t_data data;
    int rs;

    asprintf(&vals, "Users WHERE auth_token = '%s'", tok->auth_token);
    rs = mx_model_select("id", vals, callback_signin, &data);

//
//        printf("***********************************\n");
//        printf("Auth_Token: %s\n", auth_token);
//        printf("***********************************\n");

        asprintf(&vals, "login = '%s'", user->login);
        asprintf(&str, "auth_token='%s', token_aval='%u'", auth_token, mx_date_aval(864000));
        mx_model_update("Users", str, vals);
        return create_response(auth_token);
    }
    free(vals);
    return 0;
}
