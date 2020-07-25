#include "header.h"

void *mx_model_add_contact(t_add_contact *data) {
    char *vals;

    if (data) {
        asprintf(&vals, "'%d','%s'", data->contact_id, data->nick);
        mx_model_insert("Contacts", "contact_id, nick", vals);
    }
    return 0;
}
