/*
 * NAME:	Andrew Trautrim
 * EMAIL:	atrautri@uoguelph.ca
 * ID:		1072224
 */

#include "common.h"

/*
 * returns the value in the column by counting the tabs 
 */
char *get_column(char *line, int column) {
    
    char *data, c;
    int i, len, tabcount;

    i = 0;
    tabcount = 0;
    len = strlen(line);

    /* iterate until correct column is reached */
    while(tabcount < column && line[i] != '\0' && line[i] != '\n') {
        if (line[i++] == '\t') {
            tabcount++;
        }
    }

    /* get length of value in column */
    len = 0;
    while ((c = line[len++ + i]) != '\t' && c != '\0' && c != '\n');

    /* allocate memory/store value */
    data = (char *)malloc(sizeof(char) * len);
    strncpy(data, line+i, len);
    data[len-1] = '\0';
    return data;
}

/*
 * reverses a string 
 */ 
char *reverse_str(char *str) {
    char *temp;
    int length, i;
    
    /* iterates through the string backwards */
    length = strlen(str);
    temp = malloc(sizeof(char) * (length + 1));
    for (i = 0; i < length; ++i) {
        temp[i] = str[length-i-1];
    }
    temp[length-1] = '\0';

    return temp;
}