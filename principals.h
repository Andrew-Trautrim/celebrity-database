/*
 * NAME:	Andrew Trautrim
 * EMAIL:	atrautri@uoguelph.ca
 * ID:		1072224
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct title_principals {
	char *nconst;
	char *characters;
	char *tconst;
};

struct data_struct *get_principals(char *directory);

void free_principals(struct title_principals *arr, long length);
void print_principals(struct title_principals *arr, long length);
void print_principals_tree(struct node *root, int depth);