/*
 * NAME:	Andrew Trautrim
 * EMAIL:	atrautri@uoguelph.ca
 * ID:		1072224
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define max(a,b) (a>b)?a:b

struct node {
	char *key;
	void *data;
	struct node *left;
	struct node *right;
};

int depth(struct node *root);

struct node *new_node(char *key, void *data);
struct node *search(struct node *root, char *key);

void add_node(struct node **root, char *key, void *data);
void free_tree(struct node *root);
