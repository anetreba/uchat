#include "header.h"

static int callback_check_user(void *data, int argc, char **argv, char **ColName) {
    ColName = NULL;
    data = NULL;
    int rs = 0;

    if (argc > 0 && argv)
        rs = 2;
    return rs;
}

static int callback_renew(void *data, int argc, char **argv, char **ColName) {
    t_data *udata = (t_data *)data;
    ColName = NULL;

    if (argc > 0 && argv)
        udata->id = atoi(argv[0]);
    return 0;
}

int mx_check_user(int id, t_add_contact *tok) {
    char *vals;
    int rs;

    asprintf(&vals, "UsersMeta WHERE contact_id = '%d' AND user_id = '%d'", id, tok->sender_id);
    mx_model_select("id", vals, callback_check_user, &rs);
    free(vals);
    return rs;
}

t_data mx_contr_add_contact(t_add_contact *tok) {
    char *vals;
    t_data data;

    asprintf(&vals, "Users WHERE nick = '%s'", tok->nick);
    mx_model_select("id", vals, callback_renew, &data);

    data.res = mx_check_user(data.id, tok);

    asprintf(&vals, "'%d', '%d', '%s'", tok->sender_id, data.id, tok->nick);
    mx_model_insert("UsersMeta", "user_id, contact_id, nick", vals);
    free(vals);
    return data;
}
