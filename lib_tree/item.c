#include "item.h"


Item* create_item(char *value) {
    Item *item = calloc(1, sizeof(Item));
    item->value = strdup(value);
    item->next = NULL;
    return item;
}

void delete_item(Item* item){
    free(item->value);
    free(item);
}
