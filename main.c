#include <stdio.h>
#include <stdlib.h>

typedef struct Info {
    char *info;
} Info;

typedef struct Node {
    char *key;

    struct Node *left;
    struct Node *right;
    char **parent_key;
    char **next_key;
    Info *info;
} Node;

typedef struct Tree {
    Info *info;
    Node *left;
    Node *right;
} Tree;

int Tree_Show(Tree *tree) {
    printf("%s", tree->info->info);
    return 1;
}


int main() {
    Tree *tree = calloc(1, sizeof(Tree));
    Tree_Show(tree);
    printf("Hello, World!\n");
    printf("Привет\n");
    return 0;
}
