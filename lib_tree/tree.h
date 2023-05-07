#ifndef TREE_H
#define TREE_H
#include "node.h"

typedef struct Tree {
    Node *head;
} Tree;

Tree* create_tree();
void delete_tree(Tree *tree);
void delete_recur(Node *nd, char *key);
int E_Delete(Tree *tree);
void add_node(Tree *tree, char *key, char *value);
int E_Add (Tree *tree);
void my_print(Node* nd, int height, unsigned int size, int isLeft);
int Tree_Show(Tree *tree);
void find_node(Node *nd, char *key, char **res);
int E_Find(Tree *tree);
void circumvent_print(Node* nd, char *substr);
int Tree_Circumvent(Tree *tree);
void *ind_finding(Node *nd, char *key, Node **ans, int *maxim);
int E_Individual_Find(Tree *tree);


#endif
