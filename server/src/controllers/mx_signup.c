#include "header.h"

static int callback_signup(void *data, int argc, char **argv, char **ColName) {
    //t_data *udata = (t_data *)data;
    int udata = (int)data;
    ColName = NULL;

    if (argc != 0){
        udata = 1;
        argv = NULL;
        return udata;
    }
    return 0;
}

int mx_contr_signup(t_log_in *user) {
    char *vals;
    int data = 0;
    int rs = 0;

    if (user) {
        asprintf(&vals, "Users WHERE login = '%s' OR nick = '%s'", user->login, user->nick);
        rs = mx_model_select("login,nick", vals, callback_signup, &data);
        if (rs == 0) {
            asprintf(&vals, "'%s','%s','%s','%u','%s'", user->login, user->password, user->nick, 10, user->email);
            mx_model_insert("Users", "login, pass, nick, tokens, email", vals);
            return 0;
        }

    }
    return 1;
}
