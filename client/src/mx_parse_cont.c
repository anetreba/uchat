#include "header.h"


void json_parse_array_cont( json_object *jobj, char *key, t_list *list) {
    enum json_type type;
    json_object *jarray = jobj;
//    t_list *lst = list;
    t_renew_contacts *udata = (t_renew_contacts *)malloc(sizeof(t_renew_contacts));
    memset(udata, 0, sizeof(t_renew_contacts));
    if (key) {
        jarray = json_object_object_get(jobj, key);
    }

    int arraylen = json_object_array_length(jarray);
    printf("Array Length: %d\n",arraylen);
    json_object * jvalue;

    for (int i = 0; i < arraylen; i++){
        jvalue = json_object_array_get_idx(jarray, i); /*Getting the array element at position i*/
        type = json_object_get_type(jvalue);
        if (type == json_type_array) {
            json_parse_array_cont(jvalue, key, NULL);
        }
        else if (type != json_type_object) {
            if(i == 0)
                udata->contact_id = json_object_get_int(jvalue);
            if(i == 1)
                udata->nickname = strdup(json_object_get_string(jvalue));
        }
        else
            json_parse(jvalue, list);
        mx_push_back(&list, udata);
    }
}

void json_parse_cont(json_object *jobj, t_list *lst) {
    enum json_type type;

    json_object_object_foreach(jobj, key, val) {
        type = json_object_get_type(val);
        switch (type) {
            case json_type_boolean:
            case json_type_double:
            case json_type_int:
            case json_type_string:
//                print_json_value(val);
                break;
            case json_type_object:
                printf("json_type_object\n");
                jobj = json_object_object_get(jobj, key);
                json_parse(jobj, lst);
                break;
            case json_type_array:
                printf("type: json_type_array, ");
                json_parse_array_cont(jobj, key, lst);
            case json_type_null:
                break;
        }
    }
}
