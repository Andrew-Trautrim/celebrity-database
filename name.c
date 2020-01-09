/*
 * NAME:	Andrew Trautrim
 * EMAIL:	atrautri@uoguelph.ca
 * ID:		1072224
 */

#include "binary.h"
#include "common.h"
#include "name.h"

/*
 * reads in all the data of the tsv file and stores it in an array
 * returns a pointer to that array
 */
struct data_struct *get_names(char *directory) {

    struct data_struct *data;
    char buffer[256];
    char *primaryProfession, *nconst, *primaryName, *filePath;
    FILE *db;
    int len;
    long size, i;

    /* get the file path of the database */
    len = strlen(directory) + strlen("/name.basics.tsv") + 1;
    filePath = (char *)malloc(sizeof(char) * len);
    strcpy(filePath, directory);
    strcat(filePath, "/name.basics.tsv");
    db = fopen(filePath, "r");
    free(filePath);

    /* finds the size of the array to be allocated */
    size = 0;
    while (!feof(db)) {
        fgets(buffer, 256, db);
        primaryProfession = get_column(buffer, 4);
        if (strstr(primaryProfession, "actor") != NULL || strstr(primaryProfession, "actress") != NULL) {
            size++;
        }
        free(primaryProfession);
    }

    data = (struct data_struct*)malloc(sizeof(struct data_struct));
    data->arr = malloc(sizeof(struct name_basics) * size);
    data->size = size;
    data->tree1 = NULL;
    data->tree2 = NULL;

    /* iterate through the file storing the information on actors/acctresses */
    i = 0;
    fseek(db, 0, SEEK_SET);
    while (!feof(db)) {
        fgets(buffer, 256, db);

        /* stores the appropriate values in the array if the entry is an actor or actress */
        primaryProfession = get_column(buffer, 4);
        if (strstr(primaryProfession, "actor") != NULL || strstr(primaryProfession, "actress") != NULL) {

            /* get useful values */
            nconst = get_column(buffer, 0);
            primaryName = get_column(buffer, 1);

            /* insert values into arry */
            ((struct name_basics*)(data->arr))[i].nconst = nconst;
            ((struct name_basics*)(data->arr))[i].primaryName = primaryName;

            add_node(&((*data).tree1), nconst, ((struct name_basics*)(data->arr))+i);
            add_node(&((*data).tree2), primaryName, ((struct name_basics*)(data->arr))+i);

            i++;
        }
        free(primaryProfession);
    }

    fclose(db);
    return data;
}

/*
 * frees array and all the data stored from memory
 */
void free_names(struct name_basics *arr, long length) {

    long i;
    for (i = 0; i < length; ++i) {
        free(arr[i].nconst);
        free(arr[i].primaryName);
    }
    free(arr);
    return;
}

/**
 * prints the data in the array in table form
 */
void print_names(struct name_basics *arr, long length) {
    
    long i;
    printf("size: %ld\nnconst\t\tprimaryName\n", length);
    for (i = 0; i < length; ++i) {
        printf("%s\t%s\n", arr[i].nconst, arr[i].primaryName);
    }
    return;
}

void print_names_tree(struct node *root, int depth) {
    if (root) {
        printf("%3d. %s -> %p: (%s, %s)\n", depth, root->key, root->data, ((struct name_basics*)(root->data))->nconst, ((struct name_basics*)(root->data))->primaryName);
        print_names_tree(root->left, depth+1);
        print_names_tree(root->right, depth+1);
    }
}