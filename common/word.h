/* Author: Carter Person, for lab5 of CS50 20W

    This structure is designed to essentially be an implementation specific version of a counter.
    Due to the need of a different print function than the standard counter, a new implementation
    for keeping track of the counts of words was necessary. This should essentially work exactly
    like a counter besides for the print function
*/

#ifndef __WORD_H
#define __WORD_H

#include <stdio.h>


//makes a word all lowercase
char *normalize(char *word);

#endif // __WORD_H