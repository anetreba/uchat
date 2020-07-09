#include "header.h"
static t_response *create_response(char *str) {
    t_response *resp = (t_response *)malloc(sizeof(t_response));

    if(str) {
        resp->status = 0;
    }
    return resp;
}

static int callback_renew(void *data, int argc, char **argv, char **ColName) {
   // t_data *udata = (t_data *)data;
    data = NULL;
    ColName = NULL;

    if (argc > 0 && argv) {
//        udata->message = strdup(argv[0]);
//        udata->room_id = argv[1];
//        udata->room_name = strdup(argv[2]);
//        udata->sender_id = argv[3];
//        udata->date_send = argv[4];
//        udata->recieve_status = argv[5];
        for (int i = 0; i < argc; i++)
            printf("argv[%u]: %s\n", i, argv[i]);
    }
    return 0;
}

t_response mx_contr_renew(t_renew *tok) {
    char *vals;
    char *str = NULL;
    t_data data;
    int rs;

    asprintf(&vals, "Messages, Rooms "
                    "WHERE Rooms.room_id = (SELECT DISTINCT "
                    "room_id FROM Messages WHERE sender_id = ("
                    "SELECT id FROM Users WHERE auth_token = '%s') "
                    "GROUP BY Messages.room_id)", tok->auth_token);
    rs = mx_model_select("Messages.message,"
                         "    Messages.room_id,"
                         "    Rooms.room_name,"
                         "    Messages.sender_id,"
                         "    Messages.date_send,"
                         "    Messages.recieve_status",
                         vals, callback_renew, &data);

//        asprintf(&vals, "login = '%s'", user->login);
//        asprintf(&str, "auth_token='%s', token_aval='%u'", auth_token, mx_date_aval(864000));
//        mx_model_update("Users", str, vals);
        return *create_response(str);

    free(vals);

}
