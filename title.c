/*
 * NAME:	Andrew Trautrim
 * EMAIL:	atrautri@uoguelph.ca
 * ID:		1072224
 */

#include "binary.h"
#include "common.h"
#include "title.h"

/*
 * reads in all the data of the tsv file and stores it in an array
 * returns a pointer to that array
 */
struct data_struct *get_titles(char *directory) {

    struct data_struct *data;
    char buffer[256];
    char *titleType, *isAdult, *tconst, *primaryTitle, *filePath;
    FILE *db;
    int len;
    long size, i;

    /* get the file path of the database */
    len = strlen(directory) + strlen("/title.basics.tsv") + 1;
    filePath = (char *)malloc(sizeof(char) * len);
    strcpy(filePath, directory);
    strcat(filePath, "/title.basics.tsv");
    db = fopen(filePath, "r");
    free(filePath);

    /* find the size of the array to be allocated */
    size = 0;
    while (!feof(db)) {
        fgets(buffer, 256, db);
        titleType = get_column(buffer, 1);
        isAdult = get_column(buffer, 4);
        if (strstr(titleType, "movie") != NULL && strstr(isAdult, "0") != NULL) {
            size++;
        }
        free(titleType);
        free(isAdult);
    }

    data = (struct data_struct*)malloc(sizeof(struct data_struct));
    data->arr = malloc(sizeof(struct title_basics) * size);
    data->size = size;
    data->tree1 = NULL;
    data->tree2 = NULL;

    /* iterate through the file only storing the information on movies */
    i = 0;
    fseek(db, 0, SEEK_SET);
    while (!feof(db)) {
        fgets(buffer, 256, db);

        /* stores the appropriate values in the array if the entry is a movie (not an adult one) */
        titleType = get_column(buffer, 1);
        isAdult = get_column(buffer, 4);
        if (strstr(titleType, "movie") != NULL && strstr(isAdult, "0") != NULL) {

            tconst = get_column(buffer, 0);
            primaryTitle = get_column(buffer, 2);

            ((struct title_basics*)data->arr)[i].tconst = tconst;
            ((struct title_basics*)data->arr)[i].primaryTitle = primaryTitle;

            add_node(&((*data).tree1), tconst, ((struct title_basics*)(data->arr))+i);
            add_node(&((*data).tree2), primaryTitle, ((struct title_basics*)(data->arr))+i);

            i++;
        }
        free(titleType);
        free(isAdult);
    }

    fclose(db);
    return data;
}

/*
 * frees array and all the data stored from memory
 */
void free_titles(struct title_basics *arr, long length) {

    long i;
    for (i = 0; i < length; ++i) {
        free(arr[i].tconst);
        free(arr[i].primaryTitle);
    }
    free(arr);
    return;
}

/**
 * prints the data in the array in table form
 */
void print_titles(struct title_basics *arr, long length) {
    
    long i;

    printf("size: %ld\ntconst\t\tprimaryTitle\n", length);
    for (i = 0; i < length; ++i) {
        printf("%s\t%s\n", arr[i].tconst, arr[i].primaryTitle);
    }
    return;
}

void print_titles_tree(struct node *root, int depth) {
    if (root) {
        printf("%3d. %s -> %p: (%s, %s)\n", depth, root->key, root->data, ((struct title_basics*)(root->data))->tconst, ((struct title_basics*)(root->data))->primaryTitle);
        print_titles_tree(root->left, depth+1);
        print_titles_tree(root->right, depth+1);
    }
}