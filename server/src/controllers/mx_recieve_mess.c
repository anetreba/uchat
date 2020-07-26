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
    t_list *udata = (t_list *)data;
    ColName = NULL;
    t_data *data1 = (t_data *)malloc(sizeof(t_data));
    memset(data1, 0, sizeof(t_data));

    if (argc > 0 && argv) {
        data1->id = atoi(argv[1]);
        mx_push_back(&udata, data1);
    }
    return 0;
}

static void mx_select_users(t_send_message *mess, t_list *data) {
    char *vals;

    asprintf(&vals, "RoomsMeta, Users WHERE Users.id = ("
             "SELECT id FROM RoomsMeta WHERE RoomsMeta.room_id = '%d') Group BY Users.sock", mess->room_id);
    mx_model_select("RoomsMeta.user_id, Users.sock", vals, callback_select_users, data);
    free(vals);
}

void mx_create_response(t_send_message *mess, t_list *list) {
    struct json_object *jobj = json_object_new_object();
    t_list *lst = list;
    while (lst) {

            json_object_object_add(jobj, "event", json_object_new_string("new_message"));
            json_object_object_add(jobj, "status", json_object_new_string("0"));
            json_object_object_add(jobj, "room_id", json_object_new_int(mess->room_id));
            json_object_object_add(jobj, "message", json_object_new_string(mess->message));
            json_object_object_add(jobj, "sender_id", json_object_new_int(mess->sender_id));
            json_object_object_add(jobj, "date_send", json_object_new_int(mess->date_send));
            json_object_object_add(jobj, "tokens", json_object_new_int(mess->tokens));
            char *jstr = (char *) json_object_to_json_string(jobj);
            send(((t_data * )(lst->data))->id, jstr, strlen(jstr), 0);
            mx_strdel(&jstr);
            lst = lst->next;
    }
}

static int callback_tokens(void *data, int argc, char **argv, char **ColName) {
    t_data *udata = (t_data *)data;
    ColName = NULL;

    if (argc > 0 && argv) {
        udata->tokens = atoi(argv[0]);
    }
    return 0;
}

static int mx_select_user_tokens(int id) {
    char *vals;
    t_data data;

    asprintf(&vals, "Users WHERE id = '%d'", id);
    mx_model_select("tokens", vals, callback_tokens, &data);
    return data.tokens;
}

t_list *mx_recieve_mess(t_send_message *mess) {
    char *vals = NULL;
    int d = check_auth(mess);
    char *str;

    t_data *udata = (t_data *)malloc(sizeof(t_data));
    memset(udata, 0, sizeof(t_data));
    t_list *data = mx_create_node(udata);
    mess->tokens = mx_select_user_tokens(mess->sender_id);
    mess->date_send = mx_date_now();
    if (d == 0) {
        asprintf(&vals, "'%s','%d','%d','%d','%i'", mess->message, mess->sender_id,
                 mess->room_id, 0, mess->date_send);
        mx_model_insert("Messages", "message, sender_id, room_id, "
                        "recieve_status, date_send", vals);
        mx_select_users(mess, data);
        asprintf(&vals, "id = '%d'", mess->sender_id);
        asprintf(&str, "tokens = '%d'", mess->tokens - 1);
        mx_model_update("Users", str, vals);
    }
    mx_pop_front(&data);
    mx_create_response(mess, data);
    free(vals);
    return 0;
}
