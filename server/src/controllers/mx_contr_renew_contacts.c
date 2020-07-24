#include "header.h"

static int callback_renew_cont(void *data, int argc, char **argv, char **ColName) {
    t_list *lst = (t_list *)data;

    ColName = NULL;
    t_renew_contacts *udata = (t_renew_contacts *)malloc(sizeof(t_renew_contacts));
    if (argc > 0 && argv) {
        udata->contact_id = atoi(argv[0]);
        udata->nickname = strdup(argv[1]);
        mx_push_back(&lst, udata);
    }
    return 0;
}

t_list *mx_contr_renew_contacts(t_renew_contacts *tok) {
    char *vals;
    t_renew_contacts *udata = (t_renew_contacts *)malloc(sizeof(t_renew_contacts));
    memset(udata, 0, sizeof(t_renew_contacts));
    t_list *data =  mx_create_node(udata);
    int rs;

    asprintf(&vals, "UsersMeta WHERE user_id = ("
                    "SELECT id FROM Users WHERE auth_token = '%s')", tok->auth_token);
    rs = mx_model_select("DISTINCT id, nick",
                         vals, callback_renew_cont, data);
    mx_pop_front(&data);
    free(vals);
    return data;
}
