#include "header.h"

static int callback_renew(void *data, int argc, char **argv, char **ColName) {
    t_data *udata = (t_data *)data;
    ColName = NULL;

    if (argc > 0 && argv)
        udata->id = atoi(argv[0]);
    return 0;
}

int mx_contr_add_contact(t_add_contact *tok) {
    char *vals;
    t_data data;

    asprintf(&vals, "Users WHERE nick = '%s'", tok->nick);
    mx_model_select("id", vals, callback_renew, &data);

    printf("==============================================\n");
    printf("ID: %d\n", data.id);
    printf("==============================================\n");

    asprintf(&vals, "'%d', '%d', '%s'", tok->sender_id, data.id, tok->nick);
    mx_model_insert("UsersMeta", "user_id, contact_id, nick", vals);
    free(vals);
    return data.id;
}
