#include "header.h"

void mx_print(t_list *list) {
    t_list *lst = list;

    printf("err\n");
    while(lst) {
        printf("==========================ROOM============================\n");
        printf("ROOM ID = %d\n", ((t_list_room *)(lst->data))->room_id);
        printf("ROOM NAME = %s\n", ((t_list_room *)(lst->data))->room_name);
        while (((t_list_room *)(lst->data))->mess) {
            printf("*****************************************************\n");
            printf("MESSAGE = %s\n", ((t_mess *)((t_list_room *)(lst->data))->mess->data)->message);
            printf("SENDER ID = %d\n", ((t_mess *)((t_list_room *)(lst->data))->mess->data)->sender_id);
            printf("DATE SEND = %d\n", ((t_mess *)((t_list_room *)(lst->data))->mess->data)->date_send);
            printf("TYPE = %d\n", ((t_mess *)((t_list_room *)(lst->data))->mess->data)->type);
            printf("*****************************************************\n");
            ((t_list_room *)(lst->data))->mess = ((t_list_room *)(lst->data))->mess->next;
        }
        printf("============================END==========================\n");
        lst = lst->next;
    }
}

void mx_add_mess_to_list(t_event *event) {
    t_list *lst = event->list_room;

    while (lst) {
        if (((t_list_room *)(lst->data))->room_id == event->send_message->room_id) {
//            t_list *mess = ((t_list_room *)(lst->data))->mess;
            t_mess *mess = (t_mess *)malloc(sizeof(t_mess));

            mess->sender_id = event->send_message->sender_id;
            mess->date_send = event->send_message->date_send;
            mess->type = event->send_message->type;
            mess->message = strdup(event->send_message->message);
            mx_push_back(&(((t_list_room *)(lst->data))->mess), mess);
        }
        lst = lst->next;
    }
}

static int callback_rooms(void *data, int argc, char **argv, char **ColName) {
    t_list *udata = (t_list *)data;
    t_list_room *room = (t_list_room *)malloc(sizeof(t_list_room));

    memset(room, 0, sizeof(t_list_room));
    ColName = NULL;

    if (argc > 0 && argv) {
       room->room_id = atoi(argv[0]);
       room->room_name = strdup(argv[1]);
    }
//    printf("ROOM NAME = %s\n", room->room_name);
//    printf("ROOM ID = %d\n", room->room_id);
    mx_push_back(&udata, room);
    return 0;
}

static int callback_mess(void *data, int argc, char **argv, char **ColName) {
    t_list *udata = (t_list *)data;
    t_mess *mess = (t_mess *)malloc(sizeof(t_mess));

    memset(mess, 0, sizeof(t_mess));
    ColName = NULL;

    if (argc > 0 && argv) {
        mess->message = strdup(argv[0]);
        mess->sender_id = atoi(argv[1]);
        mess->date_send = atoi(argv[2]);
        if(argv[3])
            mess->type = atoi(argv[3]);
        else
            mess->type = 0;
    }
    printf("MESSAGE = %s\n", mess->message);
    printf("SENDER ID = %d\n", mess->sender_id);
    printf("DATE SEND = %d\n", mess->date_send);
    printf("TYPE = %d\n", mess->type);
    mx_push_back(&udata, mess);
    return 0;
}

void mx_sellect_mess_to_lst(t_event *event) {
    t_list *lst = event->list_room;
    char *vals2;

    while (lst) {
        t_mess *mess = (t_mess *)malloc(sizeof(t_mess));

        memset(mess, 0, sizeof(t_mess));
        ((t_list_room *)(lst->data))->mess = mx_create_node(mess);

        asprintf(&vals2, "Messages WHERE room_id = '%d'", ((t_list_room *)(lst->data))->room_id);
        mx_model_select("message, sender_id, date_send, type ", vals2, callback_mess, ((t_list_room *)(lst->data))->mess);
        mx_pop_front(&(((t_list_room *)(lst->data))->mess));
        lst = lst->next;
    }
}

void mx_listroom_and_mess(t_event *event) {
    char *vals;
    t_list_room *room = (t_list_room *)malloc(sizeof(t_list_room));

    memset(room, 0, sizeof(t_list_room));
    event->list_room = mx_create_node(room);

    asprintf(&vals, "Rooms");

    mx_model_select("room_id, room_name", vals, callback_rooms, event->list_room);
    mx_pop_front(&(event->list_room));

    mx_sellect_mess_to_lst(event);
    mx_print(event->list_room);
}
