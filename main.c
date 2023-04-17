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
    struct Node *left;			// left subtree
    struct Node *right;		// right subtree
    struct Node *parent;		// parent node
} Node;

typedef struct Tree {
    Node *head;
} Tree;


void help() {
    printf("0. Quit\n1. Add\n2. Show\n3. Individual Circumvent\n DON'T WORK--> 4. Find versions\n DON'T WORK--> 5. Perehash\n");
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

//void delete_tree(Tree* tree) {
//    delete_node_chain(tree->head);
//    free(tree);
//}


int Tree_Add (Tree *tree) {
    Node *nd = tree->head;
    printf("Input key-->");
    scanf("%*c");
    char *key = in_str();
    printf("Input info-->");
    char *value = in_str();
    Node *add = create_node(create_item(value), key);
    if (!(nd)) {
        tree->head = add;
        return 1;
    } else {
        while (nd) {
            if (strcmp(add->key, nd->key) > 0) {
                if (nd->right == NULL) {
                    nd->right = add;
                    return 1;
                }
                nd = nd->right;
            } else if (strcmp(add->key, nd->key) < 0) {
                if (nd->left == NULL) {
                    nd->left = add;
                    return 1;
                }
                nd = nd->left;
            } else {
                Item *ptr = nd->info;
                while (ptr->next) {
                    ptr = ptr->next;
                }
                ptr->next = add->info;
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
    return 1;
}


int main() {
    Tree *tree = create_tree();
    int rc;
    int (*fptr[])(Tree *) = {NULL, Tree_Add, Tree_Show, Tree_Circumvent};
    while (rc = check_command()) {
        if (!fptr[rc](tree)) break;
    }
    return 0;
}