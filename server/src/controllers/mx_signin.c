#include "header.h"

static int callback_signin(void *data, int argc, char **argv, char **ColName) {
    t_data *udata = (t_data *)data;
    //int udata = (int)data;
    ColName = NULL;
//    printf("===================CALLBACK============================\n");
//    printf("ARGC %i\n", argc);
//    printf("===================CALLBACK============================\n");


    if(argc < 2 || argv == NULL)
        return 1;

    udata->login = mx_strdup(argv[0]);
    udata->nick = mx_strdup(argv[1]);

//    printf("===================CALLBACK============================\n");
//    printf("data: %s\n", udata->login);
//    printf("data: %s\n", udata->nick);
//    for (int i = 0; i < argc; i++) {
//        printf("argc: %u\n", argc);
//        printf("argv[0]: %s\n", argv[i] ? argv[i] : "NULL");
//        printf("colName: %s\n", *ColName);
//        printf("=======================================================\n");
//    }

    return 0;
}

int mx_contr_signin(t_log_in *user) {
    char *vals;
    int data = 0;
    int rs = 0;

    asprintf(&vals, "Users WHERE login = '%s' AND pass = '%s'", user->login, user->password);
    rs = mx_model_select("login,pass", vals, callback_signin, &data);
    if (rs == 0)
        return 0;
    return 1;
}
