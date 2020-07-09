#include "header.h"

t_rnode *mx_create_rnode(void *data) {
    t_tnode *new_node = (t_tnode*)malloc(sizeof(t_tnode));

    new_node->data = data;
    new_node->left = 0;
    new_node->right = 0;
    new_node->parent = 0;
    return new_node;
}