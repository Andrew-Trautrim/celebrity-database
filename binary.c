
#include "binary.h"
#include "common.h"

/*
 * calculates/returns the max depth of the tree
 */
int depth(struct node *root) {

	/* base case, returns 0 if the current node is NULL */
	if (!root) {
		return 0;
	}

	/* returns the depth of the larger subtree */
	return max(depth(root->left), depth(root->right)) + 1;
}

/*
 * allocates memory for a new binary tree node
 */
struct node *new_node(char *key, void *data) {
	
	/* allocates mamory */
	struct node *new;
	new = (struct node*)malloc(sizeof(struct node));
	
	/* sets data */
	new->key = key;
	new->data = data;
	new->left = NULL;
	new->right = NULL;

	return new;
}

/*
 * searches for a node in the binary tree that matches the given data
 * returns the data ptr if found, NULL otherwise
 */
struct node *search(struct node *root, char *key) {

	char *reverseKey, *nodeKey;

	reverseKey = reverse_str(key);
	while(root) {
		nodeKey = reverse_str(root->key);
		if (strcmp(reverseKey, nodeKey) == 0) {
			return root;
		}

		if (strcmp(reverseKey, nodeKey) < 0) {
			root = root->left;
		} else {
			root = root->right;
		} 
		free(nodeKey);
	}

	return NULL;
}

/*
 * inserts node into the binsry tree based on the given compare function
 */
void add_node(struct node **root, char *key, void *data) {
	
	/* compares the reverse string of the keys */
	char *reverseKey, *nodeKey;

	/* iterates through tree until an empty location is found */
	reverseKey = reverse_str(key);
	while (*root) {
		nodeKey = reverse_str((*root)->key);
		if (strcmp(reverseKey, nodeKey) < 0) {
			root = &((**root).left);
		} else {
			root = &((**root).right);
		}
		free(nodeKey);
	}

	(*root) = new_node(key, data);
	return;	
}

/*
 * frees the binary tree from memory
 */
void free_tree(struct node *root) {
	
	if (root) {
		free_tree(root->left);
		free_tree(root->right);
		free(root);
	}
	return;
}
