/* 
All comments are from counters.h

 */


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "counters.h"
#include "memory.h"

//taken from bag.c
typedef struct countnode {
  int key;
  int count;		      
  struct countnode *next;	      // link to next node
} countnode_t;

//taken from bag.c
typedef struct counters {
  struct countnode *head;	      // head of the list of items in bag
  int length;
} counters_t;

//taken from bag.c
static countnode_t* countnode_new(int countnumber, int keynumber){
    countnode_t *node = calloc(1, sizeof(countnode_t));

    if (node == NULL) {
    // error allocating memory for node; return error
        return NULL;
  } else {
    node->key = keynumber;
    node->count = countnumber;
    node->next = NULL;
    return node;
  }
}


/* Create a new (empty) counter structure.
 *
 * We return:
 *   pointer to a new counterset; NULL if error. 
 * We guarantee:
 *   counterset is intialized empty.
 * Caller is responsible for:
 *   later calling counters_delete();
 */
counters_t *counters_new(void){
    counters_t *returner = calloc(1, sizeof(counters_t));
    if(returner == NULL){
        return NULL;
    }
    returner->length = 0;
    return returner;

}

/**************** counters_add ****************/
/* Increment the counter indicated by key.
 * 
 * Caller provides:
 *   valid pointer to counterset, and key(must be >= 0)
 * We return:
 *   the new value of the counter related to the indicated key.
 *   0 on error (if ctrs is NULL or key is negative)
 * We guarantee:
 *   counter values will always be >= 1.
 * We do:
 *  ignore if ctrs is NULL or key is negative.
 *  if the key does not yet exist, create a counter for it and initialize to 1.
 *  if the key does exist, increment its counter by 1.
 */
int counters_add(counters_t *ctrs, const int key){
    if(ctrs == NULL || key < 0){
        return 0;
    }

    countnode_t *curr = ctrs->head;
    for(int x = 0; x<ctrs->length;x++){
        if(curr->key == key){
            curr->count++;
            return curr->count;
        }
        curr = curr->next;
    }
    countnode_t *new;
    if( (new = countnode_new(1, key)) != NULL){
        new->next = ctrs->head;
        ctrs->head = new;
        ctrs->length++;
        return 1;
    }
    return 0;
    
}

/**************** counters_get ****************/
/* Return current value of counter associated with the given key.
 *
 * Caller provides:
 *   valid pointer to counterset, and key(must be >= 0)
 * We return:
 *   current value of counter associte with the given key, if present,
 *   0 if ctrs is NULL or if key is not found.   
 * Note:
 *   counterset is unchanged as a result of this call.
 */
int counters_get(counters_t *ctrs, const int key){
    if(ctrs == NULL || key < 0){
        return 0;
    }

    countnode_t *curr = ctrs->head;
    for(int x = 0; x<ctrs->length;x++){
        if(curr->key == key){
            return curr->count;
        }
        curr = curr->next;
    }

    return 0;
}

/**************** counters_set ****************/
/* Set the current value of counter associated with the given key.
 *
 * Caller provides:
 *   valid pointer to counterset, 
 *   key(must be >= 0), 
 *   counter value(must be >= 0).
 * We return:
 *   false if ctrs is NULL, if key < 0 or count < 0, or if out of memory.
 *   otherwise returns true.
 * We do:
 *   If the key does not yet exist, create a counter for it and initialize to
 *   the given value. 
 *   If the key does exist, update its counter value to the given value.
 */
bool counters_set(counters_t *ctrs, const int key, const int count){
    if(ctrs == NULL || key < 0 || count < 0){
        return false;
    }

    countnode_t *curr = ctrs->head;
    for(int x = 0; x<ctrs->length;x++){
        if(curr->key == key){
            curr->count = count;
            return true;
        }
        curr = curr->next;
    }

    countnode_t *new;
    if((new = countnode_new(count, key)) != NULL){
        new->next = ctrs->head;
        ctrs->head = new;
        ctrs->length++;
        return true;
    }

    return false;

}

/**************** counters_print ****************/
/* Print all counters; provide the output file.
 *
 * Caller provides:
 *   valid pointer to counterset, 
 *   FILE open for writing.
 * We print:
 *   Nothing if NULL fp. 
 *   "(null)" if NULL ctrs.
 *   otherwise, comma=separated list of key=counter pairs, all in {brackets}.
 */
void counters_print(counters_t *ctrs, FILE *fp){
    if(fp == NULL){
        return;
    }
    if(ctrs == NULL){
        fprintf(fp, "(null)");
    }
    else{
        fprintf(fp,"{ ");
        countnode_t *curr = ctrs->head;
        for(int x = 0; x<ctrs->length;x++){
            fprintf(fp, "%d = %d", curr->key, curr->count);
            curr = curr->next;
            if(curr != NULL){
                fprintf(fp, ", ");
            }
        }
        fprintf(fp, " } \n");
    }
}

/**************** counters_iterate ****************/
/* Iterate over all counters in the set.
 *
 * Caller provides:
 *   valid pointer to counterset, 
 *   arbitrary void*arg,
 *   valid pointer to itemfunc that can handle one item.
 * We do:
 *   nothing, if ctrs==NULL or itemfunc==NULL.
 *   otherwise, call itemfunc once for each item, with (arg, key, count).
 * Note:
 *   the order in which items are handled is undefined.
 *   the counterset is unchanged by this operation.
 */
void counters_iterate(counters_t *ctrs, void *arg, void (*itemfunc)(void *arg, const int key, const int count)){
    if(ctrs != NULL && itemfunc != NULL){
        countnode_t *curr = ctrs->head;
        for(int x = 0; x<ctrs->length;x++){
            itemfunc(arg, curr->key, curr->count);
            curr = curr->next;
        }
    }
}
                                        
                                       

/**************** counters_delete ****************/
/* Delete the whole counterset.
 *
 * Caller provides:
 *   a valid pointer to counterset.
 * We do:
 *   we ignore NULL ctrs.
 *   we free all memory we allocate for this counterset.
 */
void counters_delete(counters_t *ctrs){
    if(ctrs != NULL){
        countnode_t *curr = ctrs->head;
        countnode_t *deleter;
        while(curr != NULL){
            deleter = curr;
            curr = curr->next;
            free(deleter);
        }
        free(ctrs);
    }
}
