#include "header.h"

static int callback_verify(void *data, int argc, char **argv, char **ColName) {
    t_data *udata = (t_data *)data;
    ColName = NULL;

    if (argc > 0 && argv) {
        udata->nick = strdup(argv[0]);
        udata->email = strdup(argv[1]);
        udata->verify_code = atoi(argv[2]);
    }
    return 0;
}
void mx_verify_mail(char *login) {
    t_data data;
    const char *code;
    char *vals;
    int rs;

    asprintf(&vals, "Users WHERE login = '%s'", login);
    rs = mx_model_select("nick,email,verify_code", vals, callback_verify, &data);
    if (data.verify_code) {
        code = mx_itoa(data.verify_code);
        mx_sendmail(data.email, "noreply@ucaht.com,", "USER VERIFICATION", code);
    }
}
