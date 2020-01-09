/*
 * NAME:	Andrew Trautrim
 * EMAIL:	atrautri@uogeulph.ca
 * ID:		1072224
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct name_basics {
	char *nconst;
	char *primaryName;
};

int compare_nonst(const void *a, const void *b);
int compare_primaryName(const void *a, const void *b);

struct data_struct *get_names(char *directory);

void free_names(struct name_basics *arr, long length);
void print_names(struct name_basics *arr, long length);
void print_names_tree(struct node *root, int depth);