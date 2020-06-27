#include "header.h"

static int callback_signup(void *data, int argc, char **argv, char **ColName) {
    //t_data *udata = (t_data *)data;
    int udata = (int)data;
    ColName = NULL;

    if (argc != 0){
        udata = 1;
        argv = NULL;
        //mx_del_strarr(&argv);
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

int mx_contr_signup(const char *log_in, const char *pass, const char *nickname) {
    char *vals;
    int data = 0;
    int rs = 0;

    asprintf(&vals, "Users WHERE login = '%s' OR nick = '%s'", log_in, nickname);
    rs = mx_model_select("login, nick", vals, callback_signup, &data);


    if (rs == 0) {
        asprintf(&vals, "'%s','%s','%s'", log_in, pass, nickname);
        mx_model_insert("Users", "login, pass, nick", vals);
        return 0;
    }
    return 1;
}
