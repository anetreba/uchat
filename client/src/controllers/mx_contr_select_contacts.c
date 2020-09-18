#include "header.h"

void mx_print_list2(t_list *lst) {
    t_list *list = lst;
    while(list) {
        printf("3434********************************************************\n");
        printf("CONTACT_ID = %d\n",((t_renew_contacts *)(list->data))->contact_id);
        printf("CONTACT_NICK = %s\n",((t_renew_contacts *)(list->data))->nickname);
        list = list->next;
        printf("3434********************************************************\n");
    }
}

static int callback_contacts(void *data, int argc, char **argv, char **ColName) {
    t_list *lst = (t_list *)data;
    ColName = NULL;

    t_renew_contacts *contact = (t_renew_contacts *)malloc(sizeof(t_renew_contacts));

    if (argc > 0 && argv) {
        contact->contact_id = atoi(argv[0]);
        contact->nickname = strdup(argv[1]);
        mx_push_back(&lst, contact);
    }
    return 0;
}

void mx_contr_select_contacts(t_event *event) {
    printf("bla\n");
    char *vals;
    t_renew_contacts *contact = (t_renew_contacts *)malloc(sizeof(t_renew_contacts));
    memset(contact, 0, sizeof(t_renew_contacts));
    event->list_contact =  mx_create_node(contact);

    asprintf(&vals, "Contacts GROUP BY nick");
    mx_model_select("user_id, nick", vals, callback_contacts, event->list_contact);
    mx_pop_front(&(event->list_contact));
    free(vals);
    printf("===================11111111===================\n");
    mx_print_list2(event->list_contact);
    printf("===================11111111===================\n");

}

