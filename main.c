
#include "binary.h"
#include "common.h"
#include "name.h"
#include "principals.h"
#include "title.h"

int main(int argc, char **argv) {

	char *character, *name, *title, *nconst, *tconst;
	char *command, *key, line[64];
	int i;
	struct node *value, *iter1, *iter2;

	/* data sructure to hold data */
	struct data_struct *names;
	struct data_struct *titles;
	struct data_struct *principals;

	/* check that the correct number of arguments are passed in */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
		return -1;
	}

	/* load data into arrays */
	names = get_names(argv[1]);
	titles = get_titles(argv[1]);
	principals = get_principals(argv[1]);

	do {

		printf("> ");
		fgets(line, 64, stdin);

		i = 0;
		command = line;
		while (line[i] == ' ' && line[i] != '\n' && line[i] != '\0') { /* skip any leading whitepaces */
			command = &(line[++i]);
		}

		while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0') { /* iterate until next whitespace to get command */
			i++;
		}
		line[i++] = '\0';

		key = &(line[i]);
		while (line[i] == ' ' && line[i] != '\n' && line[i] != '\0') { /* skip any additional whitespaces */
			key = &(line[++i]);
		}

		while (line[i] != '\n' && line[i] != '\0') { /* iterate until the end of the line to get search key */
			i++;
		}
		line[i] = '\0';

		/* search for a name */
		if (strcmp(command, "name") == 0) {

			/* get nconst(s) for actor/actress */
			iter1 = search(names->tree2, key);
			while (iter1 != NULL) {
				nconst = ((struct name_basics*)(iter1->data))->nconst;

				/* get tconst(s) for nconst */
				iter2 = search(principals->tree1, nconst);
				while (iter2 != NULL) {
					character = ((struct title_principals*)(iter2->data))->characters;
					tconst = ((struct title_principals*)(iter2->data))->tconst;
					value = search(titles->tree1, tconst);

					/* print result, if it exists */
					if (value != NULL) {
						title = ((struct title_basics*)(value->data))->primaryTitle;
						printf("%s : %s\n", title, character);
					}
					iter2 = search(iter2->right, nconst);
				}
				iter1 = search(iter1->right, key);
			} 
		}
		/* search for a title */
		else if (strcmp(command, "title") == 0) {

			/* get tconst(s) for movie title */
			iter1 = search(titles->tree2, key);
			while (iter1 != NULL) {
				tconst = ((struct title_basics*)(iter1->data))->tconst;

				/* get nconst(s) for tconst */
				iter2 = search(principals->tree2, tconst);
				while (iter2 != NULL) {
					character = ((struct title_principals*)(iter2->data))->characters;
					nconst = ((struct title_principals*)(iter2->data))->nconst;
					value = search(names->tree1, nconst);

					/* print result, if it exists */
					if (value != NULL) {
						name = ((struct name_basics*)(value->data))->primaryName;
						printf("%s : %s\n", name, character);
					}
					iter2 = search(iter2->right, tconst);
				}
				iter1 = search(iter1->right, key);
			}
		}

	} while (strcmp(line, "exit") != 0);

	/* free binary trees from memory */
	free_tree(names->tree1);
	free_tree(names->tree2);
	free_tree(titles->tree1);
	free_tree(titles->tree2);
	free_tree(principals->tree1);
	free_tree(principals->tree2);

	/* free array and data pointers from memory */
	free_names((struct name_basics *)(names->arr), names->size);
	free_titles((struct title_basics*)(titles->arr), titles->size);
	free_principals((struct title_principals*)(principals->arr), principals->size);

	/* free data structures */
	free(names);
	free(titles);
	free(principals);

	return 0;
}
