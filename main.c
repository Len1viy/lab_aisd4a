#include "lib_tree/timer.h"


int main() {
    Tree *tree = create_tree();
    int rc;
    int (*fptr[])(Tree *) = {NULL, E_Add, Tree_Show, Tree_Circumvent, E_Delete, E_Find, Tree_From_File, E_Individual_Find, D_timing};
    while (rc = check_command()) {
        if (!fptr[rc](tree)) break;
    }
    delete_tree(tree);
    return 0;
}