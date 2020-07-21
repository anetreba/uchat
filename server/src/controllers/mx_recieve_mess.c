#include "header.h"

static int callback_check_auth(void *data, int argc, char **argv, char **ColName) {
    t_data *udata = (t_data *)data;
    ColName = NULL;

    if (argc > 0 && argv) {
        udata->id = atoi(argv[0]);
        udata->auth_token = strdup(argv[1]);
        return 0;
    }
    return 1;
}

static int check_auth(t_send_message *mess) {
    char *vals;
    int rs;
    t_send_message *udata = (t_send_message *)malloc(sizeof(t_send_message));
    t_list *data =  (t_list *)udata;

    asprintf(&vals, "Users WHERE id = '%d' AND auth_token = '%s'",
             mess->sender_id, mess->auth_token);
    rs = mx_model_select("DISTINCT id, auth_token, sock", vals, callback_check_auth, data);
    return rs;
}

static int callback_select_users(void *data, int argc, char **argv, char **ColName) {
    //t_list *udata = (t_list *)data;
    ColName = NULL;
    data = 0;

    if (argc > 0 && argv) {
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("ARGC: %d\n", argc);
        printf("ARGV[0]: %s\n", argv[0]);
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    }
    return 0;
}

static int mx_select_users(t_send_message *mess) {
    t_list *data = (t_list *)malloc(sizeof(t_list));
    char *vals;

    asprintf(&vals, "RoomsMeta WHERE room_id = '%d'", mess->room_id);
    mx_model_select("user_id", vals, callback_select_users, data);
    return 0;
}

t_list *mx_recieve_mess(t_send_message *mess) {
    char *vals = NULL;
    int d = check_auth(mess);

    if (d == 0) {
        asprintf(&vals, "'%s','%d','%d','%d','%i'", mess->message, mess->sender_id,
                 mess->room_id, 0, mx_date_now());
        mx_model_insert("Messages", "message, sender_id, room_id, "
                        "recieve_status, date_send", vals);
        mx_select_users(mess);
    }


    free(vals);
    return 0;
}
