#include "header.h"

static int callback_check_user(void *data, int argc, char **argv, char **ColName) {
    t_data *udata = (t_data *)data;
    memset(udata, 0, sizeof(t_data));
    ColName = NULL;
    argc = 0;

    if (atoi(argv[0]) == udata->id)
        udata->res = 2;
    else
        udata->res = 0;
    return 0;
}

int mx_check_user(t_data *data, t_add_contact *tok) {
    char *vals;

    asprintf(&vals, "UsersMeta WHERE contact_id = '%d' AND user_id = '%d'", data->id, tok->sender_id);
    mx_model_select("DISTINCT id", vals, callback_check_user, data);
    free(vals);
    return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////

static int callback_nick(void *data, int argc, char **argv, char **ColName) {
    t_data *udata = (t_data *)data;
    ColName = NULL;

    if (argc > 0 && argv)
        udata->id = atoi(argv[0]);
    else
        udata->id = 0;
    return 0;
}

t_data *mx_contr_add_contact(t_add_contact *tok) {
    char *vals;
    t_data *data = (t_data *)malloc(sizeof(t_data));
    memset(data, 0, sizeof(t_data));

    asprintf(&vals, "Users WHERE nick = '%s'", tok->nick);
    mx_model_select("id", vals, callback_nick, data);

    printf("=======================================s==========\n");
    printf("udata->id: %d\n", data->id);
    printf("=======================================s==========\n");

    if (data->id)
        mx_check_user(data, tok);
    else
        data->res = 1;



    printf("=======================================s==========\n");
    printf("RES: %d\n", data->res);
    printf("DATA ID: %d\n", data->id);
    printf("=======================================w==========\n");

    if (data->id != 0 && data->res == 0) {
        asprintf(&vals, "'%d', '%d', '%s'", tok->sender_id, data->id, tok->nick);
        mx_model_insert("UsersMeta", "user_id, contact_id, nick", vals);
    }
    free(vals);
    return data;
}
