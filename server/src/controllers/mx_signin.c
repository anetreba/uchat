#include "header.h"

static int callback_signin(void *data, int argc, char **argv, char **ColName) {
    t_data *udata = (t_data*)data;

    ColName = NULL;
    if (argc > 0) {
        udata->login = strdup(argv[0]);
        udata->password = strdup(argv[1]);
    }

    return 1;
}

int mx_contr_signin(t_log_in *user) {
    char *vals;
    t_data data;
    int rs;


    asprintf(&vals, "Users WHERE login = '%s'", user->login);
    rs = mx_model_select("login, pass", vals, callback_signin, &data);

    printf("===================CALLBACK IN CONTROLLER============================\n");
    printf("data LOGIN: %s\n", data.login);
    printf("data PASSW: %s\n", data.password);

    if (mx_strcmp(user->login, data.login) == 0 &&
        mx_strcmp(user->password, data.password) == 0)
        return 0;
    free(vals);
    return 1;
}
