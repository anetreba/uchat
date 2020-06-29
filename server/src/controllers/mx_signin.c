#include "header.h"

static int callback_signin(void *data, int argc, char **argv, char **ColName) {
    //t_data *udata = (t_data *)data;
    int udata = (int)data;
    ColName = NULL;

    if (argc != 0){
        udata = 1;
        argv = NULL;
        return udata;
    }
    return udata;

//    data->login = mx_strdup(argv[0]);
//    data->nick = mx_strdup(argv[1])

//    printf("===================CALLBACK============================\n");
//    printf("data: %s\n", data->login);
//    printf("data: %s\n", data->nick);
//    for (int i = 0; i < argc; i++) {
//        printf("argc: %u\n", argc);
//        printf("argv[0]: %s\n", argv[i] ? argv[i] : "NULL");
//        printf("colName: %s\n", *ColName);
//        printf("=======================================================\n");
//    }


}

int mx_contr_signin(const char *log_in, const char *pass) {
    char *vals;
    int data = 0;
    int rs = 0;

    asprintf(&vals, "Users WHERE login = '%s' AND pass = '%s'", log_in, pass);
    rs = mx_model_select("login,pass", vals, callback_signin, &data);
    if (rs == 0)
        return 1;
    return 0;
}
