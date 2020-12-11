#include "hashtable.h"
#include "webpage.h"
#include "word.h"
#include "index.h"
#include "counters.h"
#include "pagedir.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct index{
    hashtable_t *table;
} index_t;

char *normalize(char *word);
webpage_t *file2page(FILE *read);

/*returns a pointer to a new index struct*/
index_t *index_New(int size){
    index_t *returner = calloc(1,sizeof(index_t));
    returner->table = hashtable_new(size);
    return returner;
}

/*incremements the Id's value in the counter inside the word stored at the index at word in the index_t index.
adds a word at the word's index if that word does not have a word yet*/
void index_insert(index_t *index, char *word, const int ID){
    counters_t *temp = counters_new();
    if(hashtable_insert(index->table, word, temp) == false){
        free(temp);
    }

    counters_t *loc = hashtable_find(index->table, word);
    counters_add(loc, ID);
}


void index_insert_counters(index_t *index, char *word, counters_t *counter){
    hashtable_insert(index->table, word, counter);
}

counters_t *index_getCounter(index_t *index, char *word){
    return (counters_t *)hashtable_find(index->table, word);
}


/* takes an index and a path as input. This will go through the file at the path given and read in
the data in the file to the given index. This function will not assume that a path is valid. The
function will return false if the path is not valid and it cannot read in data from the file, and it
will return true if it successfuly reads in the data */
bool index_ReadInWebPage(index_t *index, char *dir, const int ID){
    FILE *read;
    char *IDnumber = calloc(3, sizeof(char)); //NOTE CHECK HERE
    sprintf(IDnumber, "%d", ID);
    char *path = calloc(strlen(dir)+strlen(IDnumber)+2, sizeof(char));
    strcpy(path, dir);
    strcat(path, "/");
    strcat(path, IDnumber);
    free(IDnumber);
    if((read = fopen(path, "r")) == NULL){
        free(path);
        return false;
    }

    int *pos = calloc(1,sizeof(int));
    char **word = calloc(1,sizeof(char**));
    webpage_t *page = file2page(read);
    while((*word = webpage_getNextWord(page, pos)) != NULL){
        char **inserter = calloc(1,sizeof(char**));
        *inserter = normalize(*word);
        index_insert(index, *inserter, ID);
        free(*inserter);
        free(inserter);
        free(*word);
    }

    free(pos);
    webpage_delete(page);
    free(word);
    free(path);
    fclose(read);
    return true;

}

void unitPrintCounters(void *target, const int key, const int count){
    fprintf(target, "%d %d ", key, count);
}



//adjusted print function for the counters
//for internal use so it is assumed that the values are valid
void adjusted_print(void *target, const char *key, void *item){
    fprintf(target, "%s ", key);
    counters_iterate(item, target, unitPrintCounters);
    fprintf(target, "\n");
}

/* This function will write the data in the index struct into a file at the assigned path. It will
return true upon a success, and false upon a failure */
void index_write(index_t *index, FILE *target){
    hashtable_iterate(index->table, target, adjusted_print);
}


/*will read in a file written by index_write and create a new index object that holds the information
encoded in that file */
index_t *index_ReadIndexFile(char *path){
    FILE *reader;
    if((reader = fopen(path, "r")) != NULL ){
        index_t *returner = index_New(200);
        char *word = calloc(40, sizeof(char)); // Assumption: all words are <= 39 chars in length
        int ID;
        int count;
        while(fscanf(reader,"%s ", word) == 1){
            counters_t *temp = counters_new();
            while(fscanf(reader,"%d %d ", &ID, &count) == 2){
                counters_set(temp, ID, count);
            }
            index_insert_counters(returner, word, temp);
        }
        free(word);
        fclose(reader);
        return returner;
    }
    return NULL;
}


/*hashtable delete wants a void * parameter for the function pointer, but counters_delete wants a counter.
    This function will deal with that discrepancy */
void counters_delete_specific(void *item){
    counters_delete((counters_t*)item);
}


/*Will free all memory used for the index object*/
void index_delete(index_t *index){
    hashtable_delete(index->table, counters_delete_specific);
    free(index);
}


