#ifndef TIMER_H
#define TIMER_H
#include "tree.h"
#include "time.h"

static char *file_read(FILE *file);
int Tree_From_File(Tree *tree);
void n_open(Tree *tree, FILE *file);
void D_timing();

#endif

