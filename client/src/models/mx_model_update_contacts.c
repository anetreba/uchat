#include "header.h"

static int callback_check_msg(void *data, int argc, char **argv, char **ColName) {
    ColName = NULL;

    if (argv[0]) {
        argc = 0;
        data = NULL;
        return 1;
    }
    return 0;
}

static int mx_check_contact(t_list *lst) {
    char *vals;
    int rs;

    asprintf(&vals, "Contacts WHERE contact_id = '%d' AND nick = '%s'",
             ((t_renew_contacts *)(lst->data))->contact_id,
             ((t_renew_contacts *)(lst->data))->nickname);

             rs = mx_model_select("id", vals, callback_check_msg, NULL);
    return rs;
}

static void write_data_to_db(json_object *obj, t_event *event) {
    t_renew *udata = (t_renew *)malloc(sizeof(t_renew));
    memset(udata, 0, sizeof(t_renew_contacts));
    char *vals;

    event->renew = mx_create_node(udata);

    json_parse(obj, event->renew);
    mx_pop_front(&event->renew);
    t_list *lst = event->renew;
    if (lst){
        while (lst) {
            if (mx_check_contact(lst) != 1) {
                asprintf(&vals, "'%d','%s'",
                         ((t_renew_contacts *)(lst->data))->contact_id,
                         ((t_renew_contacts *)(lst->data))->nickname);
                         mx_model_insert("Contacts", "contact_id, nick", vals);
            }
            lst = lst->next;
        }
    }
}

void mx_model_renew_contacts(t_event *event, json_object *obj) {
    char *str = (char *)json_object_to_json_string(obj);

    parse_json((const char *)str, &obj);
    write_data_to_db(obj, event);
}
