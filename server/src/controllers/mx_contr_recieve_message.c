#include "header.h"
static void mx_print_data(t_message *message) {
    printf("=================================================\n");
    printf("MESSAGE: %s\n", message->message);
    printf("SENDER_ID: %d\n", message->sender_id);
    printf("ROOMD_ID: %d\n", message->room_id);
    printf("=================================================\n");
}


static int callback_res_message(void *data, int argc, char **argv, char **ColName) {
    t_data *udata = (t_data *)data;
    ColName = NULL;

    if (argc > 0 && argv) {
        udata->auth_token = strcpy(argv[0]);
        udata->tokens = atoi(argv[1]);

    }
    return 0;
}

void mx_contr_recieve_message(t_event *event) {
    char *vals;
    t_data data;
    int rs1;
    int rs2;

    mx_print_data(event->message);

    asprintf(&vals, "Users WHERE id = '%s'", user->id);
    rs1 = mx_model_select("auth_token, tokens", vals, callback_res_message, &data);
    if (data.auth_token != NULL &&
        mx_strcmp(event->auth_token, data.auth_token) == 0) {

        asprintf(&vals, "'%s','%d','%s','%u','%s', '%d'", message->message, message->sender_id,
                message->room_id, mx_date_now());
        rs2 = mx_model_insert("Messages", "message, sender_id, room_id, date_send", vals);
    }
    free(vals);




    return data;
}
