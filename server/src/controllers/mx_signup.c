#include "header.h"

static int callback_signup(void *data, int argc, char **argv, char **ColName) {
    t_data *udata = NULL;
    data = 0;

    udata->login = argv[0];
    udata->argc = argc;
    udata->colname = ColName;
    return 0;
}

int mx_contr_signup(const char *log_in, const char *pass, const char *nickname) {
    char *vals;
    char *data = NULL;

    asprintf(&vals, "Users WHERE login = '%s'", log_in);
    mx_model_select("login", vals, callback_signup, &data);

    asprintf(&vals, "'%s','%s','%s'", log_in, pass, nickname);
    mx_model_insert("Users", "login, pass, nick", vals);
            return 0;
        //return 1;
}
