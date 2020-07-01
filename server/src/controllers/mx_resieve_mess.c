#include "header.h"

static int callback_signin(void *data, int argc, char **argv, char **ColName) {
    //t_data *udata = (t_data *)data;
    int udata = (int)data;
    ColName = NULL;
    argc = 0;



    //printf("===================CALLBACK============================\n");
    //printf("data: %s\n", udata->login);
    //    printf("data: %s\n", udata->nick);
    printf("===================CALLBACK============================\n");
    printf("argv[0]: %s\n", argv[0]);
    printf("argv[1]: %s\n", argv[1]);

    if (argv[0] && argv[1]) {
        udata = 0;
    }

    udata = 1;
    return udata;
}

int mx_contr_resieve_mess(t_log_in *user) {
    char *vals;
    //t_data data;
    int data;
    int rs = 0;



    //udata = (t_data *)malloc(sizeof(t_data));


    asprintf(&vals, "Users WHERE login = '%s' AND pass = '%s'", user->login, user->password);
    rs = mx_model_select("login,pass", vals, callback_signin, &data);

//    printf("===================CALLBACK IN CONTROLLER============================\n");
//    printf("data: %s\n", data.login);
//    printf("data: %s\n", data.nick);

    if (data == 0)
        return 0;
    return 1;
}
