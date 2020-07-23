#include "header.h"

static int callback_renew(void *data, int argc, char **argv, char **ColName) {
    t_list *lst = (t_list *)data;
    data = NULL;
    ColName = NULL;
    t_upd *udata = (t_upd *)malloc(sizeof(t_upd));

    if (argc > 0 && argv) {
        udata->user_id = strdup(argv[0]);
        udata->contact_id = atoi(argv[1]);
        udata->nickname = strdup(argv[2]);
        mx_push_back(&lst, udata);
    }
    return 0;
}

t_list *mx_contr_renew(t_renew *tok) {
    char *vals;
    t_renew_contacts *udata = (t_renew_contacts *)malloc(sizeof(t_renew_contacts));
    memset(udata, 0, sizeof(t_renew_contacts));
    t_list *data =  mx_create_node(udata);
    int rs;

    asprintf(&vals, "UsersMeta WHERE user_id = ", tok->id);
    rs = mx_model_select("DISTINCT DISTINCT id, nick",
                         vals, callback_renew, data);
    mx_pop_front(&data);
    free(vals);
    return data;

}
