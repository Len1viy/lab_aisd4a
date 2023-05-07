#ifndef NODE_H
#define NODE_H
#include "item.h"

typedef struct Node{
    char *key;
    Item *info;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

Node* create_node(Item *item, char *key);
void delete_item_from_list(Node *nd, int vers);
void delete_node_all(Node *nd);
int delete_node(Node* nd);


#endif
