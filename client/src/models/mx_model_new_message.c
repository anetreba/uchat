#include "header.h"

void *mx_model_new_message(t_send_message *data) {
    char *vals;

    if (data) {
        asprintf(&vals, "'%s','%d','%d','%d','%i'", data->message, data->sender_id,
                 data->room_id, 0, data->date_send);
        mx_model_insert("Messages", "message, sender_id, room_id, "
                                    "resieve_status, date_send", vals);

    }
    return 0;
}
