#include "header.h"

void mx_return_status_json(int status, int sock) {
    struct json_object *jobj = json_object_new_object();

    json_object_object_add(jobj, "status", json_object_new_int(status));
    printf("obj == %s\n", json_object_to_json_string(jobj));

    const char *jstr = json_object_to_json_string(jobj);
    printf("JSON  == %s\n", jstr);

    send(sock, jstr, strlen(jstr), 0);
}

void mx_sign_up_in(struct json_object *jobj, const char *ev, char **events, int sock) {
    t_event event;
    t_data *data;
    struct json_object *nick;
    struct json_object *password;
    struct json_object *login;

    data = (t_data *)malloc(sizeof(t_data));
    event.log_in = (t_log_in *)malloc(sizeof(t_log_in));
    json_object_object_get_ex(jobj, "login", &login);
    json_object_object_get_ex(jobj, "password", &password);
    json_object_object_get_ex(jobj, "nick", &nick);

    event.log_in->login = json_object_get_string(login);
    event.log_in->nick = json_object_get_string(nick);
    event.log_in->password = json_object_get_string(password);

    printf("=====================================================\n");
    printf("LOGIN = %s\n", event.log_in->login);
    printf("NICK = %s\n", event.log_in->nick);
    printf("PASSWORD = %s\n", event.log_in->password);
    printf("=====================================================\n");

    if (strcmp(ev, events[0]) == 0)
        if (mx_contr_signup(event.log_in->login, event.log_in->password, event.log_in->nick) == 1)
            printf("This User Is Registered\n");
    if (strcmp(ev, events[1]) == 0)
        if (mx_contr_signin(mx_contr_signup(event.log_in->login, event.log_in->password, event.log_in->nick) == 1)
            printf("User is logged In\n");
    int status = 1;
    mx_return_status_json(status, sock);
}

void mx_valid_event(struct json_object *jobj, int sock) {
    struct json_object *event;
    char *events[] = {"sign_up", "sign_in"};
    const char *ev;

    json_object_object_get_ex(jobj, "event", &event);
    ev = json_object_get_string(event);
    if ((strcmp(ev, events[0]) == 0) || (strcmp(ev, events[1]) == 0))
        mx_sign_up_in(jobj, ev, events, sock);
}
