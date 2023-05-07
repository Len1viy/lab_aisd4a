#ifndef ITEM_H
#define ITEM_H
#include "input.h"
typedef struct Item {
    char *value;
    struct Item *next;
} Item;

Item* create_item(char *value);
void delete_item(Item* item);

#endif
