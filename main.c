#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
    char *value;
    struct Item *next;
} Item;


typedef struct Node{
    char *key;
    Item *info;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

typedef struct Tree {
    Node *head;
} Tree;


void help() {
    printf("0. Quit\n1. Add\n2. Show\n3. Individual Circumvent\n4. Delete Element by key\n5. Find\n");
}

int inp_int(int *num) {
    int n;
    do {
        n = scanf("%d", num);
        if (n < 0) return 0;
        if (n == 0) {
            printf("Error input. Try again: \n");
            scanf("%*s");
        }
    } while (n == 0);
    return 1;
}

int check_command() {
    int n = 0;
    help();
    printf("Choose a command-->");
    int f = scanf("%d", &n);
    if (f != EOF) {
        while (f != 1 || (n > 5) || (n < 0)) {
            help();
            printf("Wrong input. Try again-->");
            scanf("%*[^\n]");
            if (f != EOF) {
                f = scanf("%d", &n);
            } else return 0;
        }
    } else return 0;
    return n;
}

int myln(const char *st) {
    int i = 0;
    while (st[i]) {
        i++;
    }
    return i;
}

void summator(char *res, char *sm, size_t n)
{
    int i = 0;

    if (n == 0) {
        return;
    }
    while (i < n) {
        res[i] = sm[i];
        i++;
    }
}



char *in_str() {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            return NULL;
        } else if (n > 0) {
            int chunck_len = myln(buf);
            int len_all = len + chunck_len;
            res = realloc(res, len_all + 1);
            summator(&res[len], buf, chunck_len);
            len = len_all;
        } else {
            scanf("%*c");
        }
    } while (n > 0);
    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
        res[0] = '\0';
    }
    return res;
}

Tree* create_tree(){
    Tree* tree = calloc(1, sizeof (Tree));
    tree->head = NULL;
    return tree;
}

Item* create_item(char *value) {
    Item *item = calloc(1, sizeof(Item));
    item->value = strdup(value);
    item->next = NULL;
    return item;
}

Node* create_node(Item *item, char *key) {
    Node *nd = calloc(1, sizeof(Node));
    nd->key = strdup(key);
    nd->info = item;
    return nd;
}



void delete_item(Item* item){
    free(item->value);
    free(item);
}

void delete_item_from_list(Node *nd, int vers) {
    Item *ptr = nd->info, *prev = NULL;
    int cnt = 1;
    while (ptr && cnt != vers) {
        prev = ptr;
        ptr = ptr->next;
        cnt++;
    }
    if (!ptr) return;
    if (ptr == nd->info) nd->info = ptr->next;
    if (prev) prev->next = ptr->next;
    delete_item(ptr);
}

void delete_node_all(Node *nd) {
    if (nd == NULL) return;
    if (nd->left != NULL) delete_node_all(nd->left);
    if (nd->right != NULL) delete_node_all(nd->right);
    while(nd->info) {
        delete_item_from_list(nd, 1);
    }
    nd->left = NULL;
    nd->right = NULL;
    nd->parent = NULL;
    free(nd->key);
    free(nd);
}

void delete_tree(Tree *tree) {
    delete_node_all(tree->head);
    free(tree);
}

int delete_node(Node* nd){
    Item *ptr = nd->info;
    int n = 0, cur = 0;
    if (ptr->next) {
        printf("Input the number of the element to be removed-->");
        inp_int(&n);
        delete_item_from_list(nd, n);
        return 0;
    } else {
        nd->left = NULL;
        nd->right = NULL;
        delete_item(nd->info);
        free(nd->key);
        free(nd);
        return 1;
    }

}

void delete_recur(Node *nd, char *key) {
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
            Node *min_node = nd->right, *prevert = nd->right;
            while (min_node->left != NULL) {
                prevert = min_node;
                min_node = min_node->left;
            }
            prevert->left = min_node->right;
            nd->right->parent = min_node;
            min_node->right = nd->right;
            nd->left->parent = min_node;
            min_node->left = nd->left;
            if (nd->parent->right == nd){
                min_node->parent = nd->parent;
                nd->parent->right = min_node;
            }
            if (nd->parent->left == nd){
                min_node->parent = nd->parent;
                nd->parent->left = min_node;
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
    if (tree->head == NULL) {
        printf("Tree is empty");
        return 1;
    }
    printf("Input key, which you want to delete-->");
    scanf("%*c");
    char *key = in_str();
    if (strcmp(tree->head->info->value, key) == 0) {
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
            Node *min_node = tree->head->right, *prev = tree->head->right;

            while (min_node->left != NULL) {
                prev = min_node;
                min_node = min_node->left;
            }

            prev->left = min_node->right;
            min_node->right = tree->head->right;
            min_node->left = tree->head->left;
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



int E_Add (Tree *tree) {
    Node *nd = tree->head;
    printf("Input key-->");
    scanf("%*c");
    char *key = in_str();
    printf("Input info-->");
    char *value = in_str();
    Node *add = create_node(create_item(value), key);
    free(key);
    free(value);
    if (!(nd)) {
        tree->head = add;
        return 1;
    } else {
        while (nd) {
            if (strcmp(add->key, nd->key) > 0) {
                if (nd->right == NULL) {
                    nd->right = add;
                    nd->right->parent = nd;
                    return 1;
                }
                nd = nd->right;
            } else if (strcmp(add->key, nd->key) < 0) {
                if (nd->left == NULL) {
                    nd->left = add;
                    nd->left->parent = nd;
                    return 1;
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

                return 1;
            }
        }
    }
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


int main() {
    Tree *tree = create_tree();
    int rc;
    int (*fptr[])(Tree *) = {NULL, E_Add, Tree_Show, Tree_Circumvent, E_Delete, E_Find};
    while (rc = check_command()) {
        if (!fptr[rc](tree)) break;
    }
    delete_tree(tree);
    return 0;
}