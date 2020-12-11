


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "word.h"


char *normalize(char *word){
    char *returner = calloc(strlen(word)+1,sizeof(char));
    char *curr = calloc(2, sizeof(char));
    for(int x = 0; x<strlen(word); x++){
        curr[0] = word[x];
        curr[0] = (char)tolower((int)curr[0]);
        strcat(returner, curr);
    }
    free(curr);
    return returner;
}
