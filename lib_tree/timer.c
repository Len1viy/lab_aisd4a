#include "timer.h"


static char *file_read(FILE *file) {
    char *input = malloc(sizeof (char));
    input[0] = '\0';

    char buf[81] = {0};
    int flag = 1, length = 0, buf_len;
    while (flag > 0) {
        flag = fscanf(file, "%80[^\n]", buf);
        if (flag == EOF) {
            free(input);
            return NULL;
        }
        if (!flag)
            fscanf(file, "%*c");
        else {
            buf_len = strlen(buf);
            length += buf_len;
            input = realloc(input, length + 1);
            memcpy(input + length - buf_len, buf, buf_len * sizeof (char));
            input[length] = '\0';
        }
    }
    return input;
}

int Tree_From_File(Tree *tree) {
//    FILE *file = fopen("text.txt", "r");
    FILE *file = fopen("C:\\Users\\vadim\\CLionProjects\\lab_aisd4a\\text.txt", "r");
    char *value = NULL, *key = NULL;
    while (!feof(file)) {
        key = file_read(file);
        value = file_read(file);
        if (key != NULL && value != NULL){
            add_node(tree, key, value);
        }

        if (value != NULL) free(value);
        if (key != NULL) free(key);
    }
    fclose(file);
    Tree_Show(tree);
    return 1;
}

void n_open(Tree *tree, FILE *file) {
    char *value = NULL, *key = NULL;
    for (int i = 0; i < 5000; i++) {
        key = file_read(file);
        value = file_read(file);
        if (key != NULL && value != NULL){
            add_node(tree, key, value);
        }

        if (value != NULL) free(value);
        if (key != NULL) free(key);
    }
}

void D_timing() {
    Tree *tree = create_tree();;
    FILE *file = fopen("C:\\Users\\vadim\\CLionProjects\\lab_aisd4a\\out.txt", "w");
    FILE *timer = fopen("C:\\Users\\vadim\\CLionProjects\\lab_aisd4a\\timer.txt", "r");
    printf("INPUT KEY -->");
    scanf("%*c");
    char *key = in_str();
    clock_t start, end;
    for (int i = 0; i < 1000000; i += 10000) {

        n_open(tree, timer);
        printf("percent: %d\n", i / 10000);

        start = clock();
        add_node(tree, key, 0);
        end = clock();
        fprintf(file, "INSERT %lf\n", (double ) (end - start) / CLOCKS_PER_SEC);
        printf("OK1\n");

        start = clock();
        delete_recur(tree->head, key);
        end = clock();
        fprintf(file, "DELETE %lf\n", (double ) (end - start) / CLOCKS_PER_SEC);
        printf("OK2\n");

        start = clock();
        circumvent_print(tree->head, "a");
        end = clock();
        fprintf(file, "CIRCUMVENT %lf\n", (double ) (end - start) / CLOCKS_PER_SEC);
        printf("OK3\n");

        char *result;
        start = clock();
        find_node(tree->head, key, &result);
        end = clock();
        fprintf(file, "FIND %lf\n", (double ) (end - start) / CLOCKS_PER_SEC);
        printf("OK4\n");


        Node *ans;
        int maxim = 1000000;
        start = clock();
        ind_finding(tree->head, key, &ans, &maxim);
        end = clock();
        fprintf(file, "INDIVIDUAL_FIND %lf\n", (double ) (end - start) / CLOCKS_PER_SEC);
        printf("OK5\n");

    }
    fclose(file);
    fclose(timer);
    if (tree != NULL) delete_tree(tree);
}