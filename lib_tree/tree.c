#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"


Tree* create_tree(){
    Tree* tree = calloc(1, sizeof (Tree));
    tree->head = NULL;
    return tree;
}

void delete_tree(Tree *tree) {
    delete_node_all(tree->head);
    free(tree);
}


void delete_recur(Node *nd, char *key) {
    if (nd == NULL) {
        printf("Key doesn'n exist\n");
        return;
    }
    if (strcmp(key, nd->key) == 0){
        if (nd->info->next) {
            int n;
            printf("Input the number of the element to be removed-->");
            inp_int(&n);
            delete_item_from_list(nd, n);
            return;
        }
        if (nd->left == NULL && nd->right == NULL){
            if (nd->parent->left == nd){
                nd->parent->left = NULL;
            }
            if (nd->parent->right == nd){
                nd->parent->right = NULL;
            }
            delete_node(nd);
            return;
        }
        if (nd->left == NULL && nd->right != NULL){
            if (nd->parent->left == nd){
                nd->right->parent = nd->parent;
                nd->parent->left = nd->right;

            }
            if (nd->parent->right == nd){
                nd->right->parent = nd->parent;
                nd->parent->right = nd->right;
            }
            delete_node(nd);
            return;
        }
        if (nd->left != NULL && nd->right == NULL){
            if (nd->parent->left == nd){
                nd->left->parent = nd->parent;
                nd->parent->left = nd->left;
            }
            if (nd->parent->right == nd){
                nd->left->parent = nd->parent;
                nd->parent->right = nd->left;
            }
            delete_node(nd);
            return;
        }
        if (nd->left != NULL && nd->right != NULL) {
            Node *min_node = nd->right;
            while (min_node->left != NULL) {
                min_node = min_node->left;
            }
            if (min_node->parent == nd) {
                min_node->left = nd->left;
                nd->left->parent = min_node;
            } else {
                if (min_node->right) {
                    min_node->parent->left = min_node->right;
                    min_node->right->parent = min_node->parent;
                } else {
                    min_node->parent->left = NULL;
                }
                min_node->left = nd->left;
                min_node->right = nd->right;
                if (min_node->left) min_node->left->parent = min_node;
                if (min_node->right) min_node->right->parent = min_node;
            }
            min_node->parent = nd->parent;
            if (nd->parent->left == nd) {
                printf("LEFT\n");
                nd->parent->left = min_node;
            }
            else {
                printf("RIGHT\n");
                nd->parent->right = min_node;
            }
            delete_node(nd);

            return;
        }
    }
    if (strcmp(key, nd->key) < 0){
        delete_recur(nd->left, key);
    }
    if (strcmp(key, nd->key) > 0){
        delete_recur(nd->right, key);
    }
}

int E_Delete(Tree *tree) {
    printf("%s", tree->head->key);
    if (tree->head == NULL) {
        printf("Tree is empty");
        return 1;
    }
    printf("Input key, which you want to delete-->");
    scanf("%*c");
    char *key = in_str();
    if (strcmp(tree->head->key, key) == 0) {
        if (tree->head->info->next) {
            int n;
            printf("Input the number of the element to be removed-->");
            inp_int(&n);
            delete_item_from_list(tree->head, n);
            free(key);
            return 1;
        }
        if (tree->head->left == NULL && tree->head->right == NULL) {
            int f = delete_node(tree->head);
            printf("DELETED\n");
            if (f == 1) tree->head = NULL;
            free(key);
            return 1;
        }
        if (tree->head->left == NULL && tree->head->right != NULL) {
            Node *temp = tree->head->right;
            int f = delete_node(tree->head);
            if (f == 1) tree->head = temp;
            free(key);
            return 1;
        }
        if (tree->head->left != NULL && tree->head->right == NULL) {
            Node *temp = tree->head->left;
            int f = delete_node(tree->head);
            if (f == 1) tree->head = temp;
            free(key);
            return 1;
        }

        if (tree->head->left != NULL && tree->head->right != NULL) {
            Node *min_node = tree->head->right;

            while (min_node->left != NULL) {
                min_node = min_node->left;
            }
            if (min_node->parent == tree->head) {
                min_node->left = tree->head->left;
                tree->head->left->parent = min_node;
            } else {
                if (min_node->right) {
                    min_node->parent->left = min_node->right;
                    min_node->right->parent = min_node->parent;
                } else {
                    min_node->parent->left = NULL;
                }
                min_node->left = tree->head->left;
                min_node->right = tree->head->right;
                if (min_node->left) min_node->left->parent = min_node;
                if (min_node->right) min_node->right->parent = min_node;
            }
            min_node->parent = NULL;
            int f = delete_node(tree->head);
            if (f == 1) tree->head = min_node;
            free(key);
            return 1;
        }
    } else {
        delete_recur(tree->head, key);
        free(key);
        return 1;
    }
}


void add_node(Tree *tree, char *key, char *value) {
    Node *nd = tree->head;
    Node *add = create_node(create_item(value), key);
    if (!(nd)) {
        tree->head = add;
        return;
    } else {
        while (nd) {
            if (strcmp(add->key, nd->key) > 0) {
                if (nd->right == NULL) {
                    nd->right = add;
                    nd->right->parent = nd;
                    return;
                }
                nd = nd->right;
            } else if (strcmp(add->key, nd->key) < 0) {
                if (nd->left == NULL) {
                    nd->left = add;
                    nd->left->parent = nd;
                    return;
                }
                nd = nd->left;
            } else {
                Item *ptr = nd->info;
                while (ptr->next) {
                    ptr = ptr->next;
                }
                ptr->next = add->info;
                free(add->key);
                free(add);

                return;
            }
        }
    }
}


int E_Add (Tree *tree) {
    Node *nd = tree->head;
    printf("Input key-->");
    scanf("%*c");
    char *key = in_str();
    printf("Input info-->");
    char *value = in_str();
    add_node(tree, key, value);
    free(key);
    free(value);
}

void my_print(Node* nd, int height, unsigned int size, int isLeft){
    if (nd->right != NULL){
        my_print(nd->right, height + 1, size + strlen(nd->key), 0);
    }

    if (size == 0){
        printf("----%s|\n", nd->key);
    }
    else {

        if (isLeft == 0) {
            for (int i = 0; i < size + height * 4; i++) {
                printf(" ");
            }
            printf("___%s|\n", nd->key);
        } else {
            for (int i = 0; i < size + height * 4; i++){
                printf(" ");
            }
            printf("~~~%s|\n", nd->key);
        }
    }

    if (nd->left != NULL){
        my_print(nd->left, height + 1, size + strlen(nd->key), 1);
    }
}

int Tree_Show(Tree *tree) {
    if (tree->head == NULL){
        printf("Tree is Empty\n");
        return 1;
    }

    printf("\nTree: \n\n");
    my_print(tree->head, 0, 0, 0);
    return 1;
}

char *find_item(Item *item, int vers) {
    int cnt = 1;
    while (item && cnt != vers) {
        item = item->next;
        cnt++;
    }
    if (!item) return "THAT'S VERSION DOESN'T EXIST";
    return item->value;
}

void find_node(Node *nd, char *key, char **res) {
    if (strcmp(key, nd->key) == 0) {
        if (nd->info->next) {
            printf("Input, which version you want to find-->");
            int v;
            inp_int(&v);
            (*res) = find_item(nd->info, v);
            return;
        } else (*res) = strdup(nd->info->value);
    }
    if (strcmp(key, nd->key) > 0) {
        if (nd->right == NULL) return;
        find_node(nd->right, key, res);
    }
    if (strcmp(key, nd->key) < 0) {
        if (nd->left == NULL) return;
        find_node(nd->left, key, res);
    }
}

int E_Find(Tree *tree) {
    if (tree->head == NULL) {
        printf("Tree is empty\n");
        return 1;
    }
    printf("Input key, which you want to find-->");
    scanf("%*c");
    char *key = in_str();
    char *result;
    find_node(tree->head, key, &result);
    printf("VALUE ---> %s\n", result);
    free(key);
    free(result);
    return 1;
}


void circumvent_print(Node* nd, char *substr){

    if (nd->right != NULL){
        circumvent_print(nd->right, substr);
    }

    if (strncmp(nd->key, substr, strlen(substr)) == 0) {
        int len = 0;
        printf("|%s", nd->info->value);
        len += strlen(nd->info->value);
        Item *ptr = nd->info->next;
        while (ptr) {
            printf(", %s", ptr->value);
            len += strlen(ptr->value) + 2;
            ptr = ptr->next;
        }
        for (int i = 0; i < 98 - len - strlen(nd->key); i++) {
            if (i == (49 - len)) printf("|");
            else printf(" ");
        }
        printf("%s|\n", nd->key);
    }

    if (nd->left != NULL){
        circumvent_print(nd->left, substr);
    }
}

int Tree_Circumvent(Tree *tree) {
    if (tree->head == NULL){
        printf("Tree is Empty\n");
        return 1;
    }
    printf("Input Substing-->");
    scanf("%*c");
    char *subString = in_str();
    printf("\n");
    int i = 0;
    while (i < 100) {
        if (i == 0 || i == 50 || i == 99) {
            printf("|");
        } else if (i == (101 / 4)) {
            printf("val");
            i += 2;
        } else if (i == (101 / 4) * 3) {
            printf("key");
            i += 2;
        } else printf(" ");
        i++;
    }
    printf("\n");
    for (int i = 0; i < 100; i++) {
        printf("-");
    }
    printf("\n");
    circumvent_print(tree->head, subString);
    free(subString);
    return 1;
}

void *ind_finding(Node *nd, char *key, Node **ans, int *maxim) {
    if (nd->right != NULL){
        ind_finding(nd->right, key, ans, maxim);
    }
    char *lower;
    if (strlen(key) > strlen(nd->key)) lower = strdup(nd->key);
    else lower = strdup(key);
    int razn = 0;
    for (int elem = 0; elem < strlen(lower); elem++) {
        if (key[elem] > nd->key[elem]) razn += key[elem] - nd->key[elem];
        else razn += nd->key[elem] - key[elem];
    }
    if (razn > (*maxim)) {
        *maxim = razn;
        *ans = nd;
    }
    free(lower);
    if (nd->left != NULL){
        ind_finding(nd->left, key, ans, maxim);
    }
}

int E_Individual_Find(Tree *tree) {
    printf("Input key --> ");
    scanf("%*c");
    char *finding = in_str();
    Node *ans;
    int maxim = 0;
    ind_finding(tree->head, finding, &ans, &maxim);
    printf("KEY - %s; INFO - %s", ans->key, ans->info->value);
    Item *ptr = ans->info->next;
    while (ptr) {
        printf(", %s", ptr->value);
        ptr = ptr->next;
    }
    printf("\n");
    free(finding);
    return 1;
}