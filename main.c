#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Info {
    char *info;
} Info;

typedef struct Node {
    char *key;

    struct Node *left;
    struct Node *right;
    struct Node *parent_key;
    struct Node *next_key;
    Info info;
} Node;

typedef struct Tree {
    Node *head;
} Tree;

void help() {
    printf("0. Quit\n1. Add\n2. Show\n DON'T WORK--> 3. Delete\n DON'T WORK--> 4. Find versions\n DON'T WORK--> 5. Perehash\n");
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

int mystrcmp(char *str1, char *str2) {
    int str1_cnt = 0;
    int str2_cnt = 0;
    for (int i = 0; i < strlen(str1); i++) {
        str1_cnt += str1[i];
    }
    for (int i = 0; i < strlen(str2); i++) {
        str2_cnt += str2[i];
    }
    if (str1_cnt > str2_cnt) return 1;
    else if (str1_cnt == str2_cnt) return 0;
    else return -1;
}

int Tree_Add (Tree *tree) {
    Node *nd = tree->head;
    printf("Input key-->");
    scanf("%*c");
    char *key = in_str();
    printf("Input info-->");
    char *info = in_str();
    if (!(nd)) {
        nd = realloc(nd, sizeof(Node));
        nd->key = strdup(key);
        nd->info.info = strdup(info);
        printf("%s %s\n", nd->key, nd->info.info);
        tree->head = nd;
        return 1;
    } else {
        while (nd) {
            if (mystrcmp(key, nd->key) == 1) {
                nd = nd->right;
            } else if (mystrcmp(key, nd->key) == -1) {
                nd = nd->left;
            }
        }
        nd = realloc(nd, sizeof(Node));
        nd->key = strdup(key);
        nd->info.info = strdup(info);
    }
}

void postOrderTravers(Node* root) {
    if (root) {
        postOrderTravers(root->left);
        postOrderTravers(root->right);
        printf("%s ", root->info.info);
    } else {
        return;
    }
}

int Tree_Show(Tree *tree) {
    Node *head = tree->head;
    postOrderTravers(head);
}

int main() {
    Tree *tree = calloc(1, sizeof(Tree));
    int rc;
    int (*fptr[])(Tree *) = {NULL, Tree_Add, Tree_Show};
    while (rc = check_command()) {
        if (!fptr[rc](tree)) break;
    }
    return 0;
}
