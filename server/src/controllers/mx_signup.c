#include "header.h"

static int callback_signup(void *data, int argc, char **argv, char **ColName) {
    int udata = (int)data;
    ColName = NULL;

    if (argc != 0 && argv[0]){
        udata = 1;
        argv = NULL;
        return udata;
    }
    return 0;
}

t_signup mx_contr_signup(t_log_in *user) {
    char *vals;
    int data = 0;
    int rs = 0;
    t_signup status;
    status.status = 1;

    if (user) {
        asprintf(&vals, "Users WHERE login = '%s' OR nick = '%s'", user->login, user->nick);
        rs = mx_model_select("login,nick", vals, callback_signup, &data);
        if (rs == 0) {
            status.status = 0;
            status.verify_code = mx_gen_verify_code(6);
            asprintf(&vals, "'%s','%s','%s','%u','%s', '%d'", user->login, user->password, user->nick, 10, user->email, status.verify_code);
            mx_model_insert("Users", "login, pass, nick, tokens, email, verify_code", vals);
        }
        mx_verify_mail((char *)user->login);
    }
    return status;
}
