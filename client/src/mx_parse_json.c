#include "header.h"

int parse_json(const char *json, json_object **responses) {
    json_tokener *tok = json_tokener_new();
    int stringlen = 0;
    enum json_tokener_error jerr;

    stringlen = strlen(json);
    *responses = json_tokener_parse_ex(tok, json, stringlen);
    while ((jerr = json_tokener_get_error(tok)) == json_tokener_continue) {
        stringlen = strlen(json);
        *responses = json_tokener_parse_ex(tok, json, stringlen);
    }
    if (jerr != json_tokener_success) {
        fprintf(stderr, "JSON Error: %s\n", json_tokener_error_desc(jerr));
        return 1;
    }
    json_tokener_free(tok);
    return 0;
}

char *mx_parse_str(char *jstr, char buf) {
    int len = mx_strlen(jstr) + 1;
    char *tmp = mx_strnew(len);

    for (int i = 0; jstr[i]; i++)
        tmp[i] = jstr[i];
    tmp[len - 1] = buf;
    if (malloc_size(jstr))
        mx_strdel(&jstr);
    jstr = mx_strdup(tmp);
    if (malloc_size(tmp))
        mx_strdel(&tmp);
    return jstr;
}

void print_json_value(json_object *jobj){
    enum json_type type;

    type = json_object_get_type(jobj); /*Getting the type of the json object*/
    switch (type) {
        case json_type_boolean:
            printf("json_type_boolean\n");
            printf("value: %s\n", json_object_get_boolean(jobj)? "true": "false");
            break;
        case json_type_double:
            printf("json_type_double\n");
            printf("value: %lf\n", json_object_get_double(jobj));
            break;
        case json_type_int:
            printf("json_type_int\n");
            printf("value: %d\n", json_object_get_int(jobj));
            break;
        case json_type_string:
            printf("json_type_string\n");
            printf("value: %s\n", json_object_get_string(jobj));
            break;
        case json_type_object:
            printf("json_type_object\n");
            break;
        case json_type_array:
            printf("type: json_type_array\n");
        case json_type_null:
            break;
    }

}

void json_parse_array( json_object *jobj, char *key, t_list *list) {
    enum json_type type;
    json_object *jarray = jobj;
    t_list *lst = list;
    t_renew *udata = (t_renew *)malloc(sizeof(t_renew));

    if (key)
        jarray = json_object_object_get(jobj, key);

    int arraylen = json_object_array_length(jarray);
    printf("Array Length: %d\n",arraylen);
    json_object * jvalue;

    for (int i = 0; i < arraylen; i++){
        jvalue = json_object_array_get_idx(jarray, i); /*Getting the array element at position i*/
        type = json_object_get_type(jvalue);
        if (type == json_type_array)
            json_parse_array(jvalue, key, NULL);
        else if (type != json_type_object) {
               if(i == 1)
                   udata->room_id = json_object_get_int(jvalue);
               if(i == 2)
                   udata->name_room = strdup(json_object_get_string(jvalue));
               if(i == 3)
                   udata->message = strdup(json_object_get_string(jvalue));
               if(i == 4)
                   udata->sender_id = json_object_get_int(jvalue);
               if(i == 5)
                   udata->date_send = json_object_get_int(jvalue);
               if(i == 6)
                   udata->recieve_status = json_object_get_int(jvalue);
        }
        else
            json_parse(jvalue, list);
    }
    mx_push_back(&lst, udata);
}

void json_parse(json_object *jobj, t_list *lst) {
    enum json_type type;

    json_object_object_foreach(jobj, key, val) {
        type = json_object_get_type(val);
        switch (type) {
            case json_type_boolean:
            case json_type_double:
            case json_type_int:
            case json_type_string:
                print_json_value(val);
                break;
            case json_type_object:
                printf("json_type_object\n");
                jobj = json_object_object_get(jobj, key);
                json_parse(jobj, lst);
                break;
            case json_type_array:
                printf("type: json_type_array, ");
                json_parse_array(jobj, key, lst);
            case json_type_null:
                break;
        }
    }
}

