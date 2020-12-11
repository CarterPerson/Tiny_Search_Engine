
#ifndef __INDEX_H
#define __INDEX_H

#include "webpage.h"
#include "counters.h"
#include <stdio.h>

typedef struct index index_t;

/*returns a pointer to a new index struct*/
index_t *index_New(int size);

/*incremements the Id's value in the counter inside the word stored at the index at word in the index_t index.
adds a word at the word's index if that word does not have a word yet*/
void index_insert(index_t *index, char *word, const int ID);

// This function will insert a full counter into the index's hashtable. This is designed to help with the reading
// in of a file that was produced by printing an index.
void index_insert_counters(index_t *index, char *word, counters_t *counter);

/* takes an index, target directory, and an ID as parameters. This will go through the file at the path given and read in
the data in the file to the given index. This function will not assume that the ID and directory are valid. The
function will return false if the generated path is not valid and it cannot read in data from the file, and it
will return true if it successfuly reads in the data */
bool index_ReadInWebPage(index_t *index, char *dir, const int ID);


/* This function will write the data in the index struct into a file at the assigned path. It will
return true upon a success, and false upon a failure */
void index_write(index_t *index, FILE *target);


/*will read in a file written by index_write and create a new index object that holds the information
encoded in that file */
index_t *index_ReadIndexFile(char *path);


//returns the counters associated with the input word
counters_t *index_getCounter(index_t *index, char *word);


/* helper function designed for internal use only (thus it assumes that all inputs are correct).
    This function will take a file made by crawler that is open for reading, and read the data 
    back into a webpage object. */
webpage_t *file2page(FILE *read);


/*Will free all memory used for the index object*/
void index_delete(index_t *index);

#endif // __INDEX_H
