#include "node.h"


Node* create_node(Item *item, char *key) {
    Node *nd = calloc(1, sizeof(Node));
    nd->key = strdup(key);
    nd->info = item;
    return nd;
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
