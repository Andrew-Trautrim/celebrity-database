/*
 * NAME:	Andrew Trautrim
 * EMAIL:	atrautri@uoguelph.ca
 * ID:		1072224
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data_struct {
    void *arr; /* points to array */
    long size; /* size of list */
    struct node *tree1;
    struct node *tree2;
};

char *get_column(char *line, int column);
char *reverse_str(char *str);
