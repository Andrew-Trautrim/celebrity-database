/*
 * NAME:	Andrew Trautrim
 * EMAIL:	atrautri@uogeulph.ca
 * ID:		1072224
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct title_basics {
	char *tconst;
	char *primaryTitle;
};

int compare_names(const void *a, const void *b);

struct data_struct *get_titles(char *directory);

void free_titles(struct title_basics *arr, long length);
void print_titles(struct title_basics *arr, long length);
void print_titles_tree(struct node *root, int depth);
