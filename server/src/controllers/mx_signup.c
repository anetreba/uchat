#include "header.h"

void mx_contr_signup(const char *log_in, const char *pass, const char *nickname) {
//    const char log_in = *login->login;
//    const char pass = *login->password;
//    const char nickname = *login->nick;
    char *vals;

    asprintf(&vals, "'%s','%s','%s'", log_in, pass, nickname);
    mx_model_insert("Users", "login, pass, nickname", vals);
}
