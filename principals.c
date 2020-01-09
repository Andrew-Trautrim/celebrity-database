/*
 * NAME:	Andrew Trautrim
 * EMAIL:	atrautri@uoguelph.ca
 * ID:		1072224
 */

#include "binary.h"
#include "common.h"
#include "principals.h"

/*
 * reads in all the data of the tsv file and stores it in an array
 * returns a pointer to that array
 */
struct data_struct *get_principals(char *directory) {

    struct data_struct *data;
    char buffer[256];
    char *catagory, *nconst, *tconst, *characters, *filePath;
    FILE *db;
    int len;
    long size, i;

    /* get the file path of the database */
    len = strlen(directory) + strlen("/title.principals.tsv") + 1;
    filePath = (char *)malloc(sizeof(char) * len);
    strcpy(filePath, directory);
    strcat(filePath, "/title.principals.tsv");
    db = fopen(filePath, "r");
    free(filePath);

    /* find the size of the array to be allocated */
    size = 0;
    while (!feof(db)) {
        fgets(buffer, 256, db);

        catagory = get_column(buffer, 3);
        if (strstr(catagory, "actor") != NULL || strstr(catagory, "actress") != NULL) {
            size++;
        }
        free(catagory);
    }

    data = (struct data_struct*)malloc(sizeof(struct data_struct));
    data->arr = malloc(sizeof(struct title_principals) * size);
    data->size = size;
    data->tree1 = NULL;
    data->tree2 = NULL;

    /* iterate through the file storing the information on characters */
    i = 0;
    fseek(db, 0, SEEK_SET);
    while (!feof(db)) {
        fgets(buffer, 256, db);

        /* stores the appropriate values in the array if the entry is a movie */
        catagory = get_column(buffer, 3);
        if (strstr(catagory, "actor") != NULL || strstr(catagory, "actress") != NULL) {

            /* stores the appropriate values if the entry is an actor or actress */
            tconst = get_column(buffer, 0);
            nconst = get_column(buffer, 2);
            characters = get_column(buffer, 5);

            ((struct title_principals*)data->arr)[i].nconst = nconst;
            ((struct title_principals*)data->arr)[i].characters = characters;
            ((struct title_principals*)data->arr)[i].tconst = tconst;

            add_node(&((*data).tree1), nconst, ((struct title_principals*)(data->arr))+i);
            add_node(&((*data).tree2), tconst, ((struct title_principals*)(data->arr))+i);

            i++;
        }
        free(catagory);
    }

    fclose(db);
    return data;
}

/*
 * frees array and all the data stored from memory
 */
void free_principals(struct title_principals *arr, long length) {

    long i;
    for (i = 0; i < length; ++i) {
        free(arr[i].tconst);
        free(arr[i].nconst);
        free(arr[i].characters);
    }
    free(arr);
    return;
}

/**
 * prints the data in the array in table form
 */
void print_principals(struct title_principals *arr, long length) {
    
    long i;
    printf("size: %ld\nnconst\t\ttconst\t\tcharacters\n", length);
    for (i = 0; i < length; ++i) {
        printf("%s\t%s\t%s\n", arr[i].nconst, arr[i].tconst, arr[i].characters);
    }
    return;
}

void print_principals_tree(struct node *root, int depth) {
    if (root) {
        printf("%3d. %s -> %p: (%s, %s, %s)\n", depth, root->key, root->data, ((struct title_principals*)(root->data))->nconst, ((struct title_principals*)(root->data))->characters, ((struct title_principals*)(root->data))->tconst);
        print_principals_tree(root->left, depth+1);
        print_principals_tree(root->right, depth+1);
    }
}