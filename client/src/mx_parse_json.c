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
