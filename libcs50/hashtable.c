
//note: I copied and pasted the base for this from hashtable.h, so most comments are from there

/* Hashtable is an implementation of a superior sorting method than lists.
 * Each key will be hashed into an integer value, which will be the index
 * of the set where it will be placed */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "set.h" //I'm implementing each hash value as a set of all keys that hash into it
#include "hashtable.h"
#include "jhash.h"

/**************** global types ****************/
typedef struct hashtable{
    int num_slots;
    set_t **table;
} hashtable_t;  // opaque to users of the module

/**************** hashtable_new ****************/
/* Create a new (empty) hashtable.
 *
 * Caller provides:
 *   number of slots to be used for the hashtable (must be > 0).
 * We return:
 *   pointer to the new hashtable; return NULL if error.
 * We guarantee:
 *   hashtable is initialized empty.
 * Caller is responsible for:
 *   later calling hashtable_delete.
 */
hashtable_t *hashtable_new(const int num_slots){
    if((num_slots>0)){
        hashtable_t *returner = (hashtable_t *)calloc(1, sizeof(hashtable_t));
        returner->num_slots = num_slots;
        returner->table = (set_t**) calloc(num_slots, sizeof(set_t*));
        for(int x = 0; x<num_slots; x++){
            returner->table[x] = set_new();
        }
        return returner;
    }
    return NULL;

}

/**************** hashtable_insert ****************/
/* Insert item, identified by key (string), into the given hashtable.
 *
 * Caller provides:
 *   valid pointer to hashtable, valid string for key, valid pointer for item.
 * We return:
 *   false if key exists in ht, any parameter is NULL, or error;
 *   true iff new item was inserted.
 * Notes:
 *   The key string is copied for use by the hashtable; that is, the module
 *   is responsible for allocating memory for a copy of the key string, and
 *   later deallocating that memory; thus, the caller is free to re-use or 
 *   deallocate its key string after this call.  
 */
bool hashtable_insert(hashtable_t *ht, const char *key, void *item){
    if(ht == NULL || key == NULL || item == NULL){
        return false;
    }
    unsigned long index = JenkinsHash(key, (unsigned long) ht->num_slots);
    set_t *location = ht->table[index];

    return (set_insert(location, key, item));

}

/**************** hashtable_find ****************/
/* Return the item associated with the given key.
 *
 * Caller provides:
 *   valid pointer to hashtable, valid string for key.
 * We return:
 *   pointer to the item corresponding to the given key, if found;
 *   NULL if hashtable is NULL, key is NULL, or key is not found.
 * Notes:
 *   the hashtable is unchanged by this operation.
 */
void *hashtable_find(hashtable_t *ht, const char *key){
    if(ht == NULL || key == NULL){
        return NULL;
    }
    unsigned long index = JenkinsHash(key, (unsigned long) ht->num_slots);
    set_t *location = ht->table[index];

    return (set_find(location, key));


}

/**************** hashtable_print ****************/
/* Print the whole table; provide the output file and func to print each item.
 * 
 * Caller provides:
 *   valid pointer to hashtable, 
 *   FILE open for writing,
 *   itemprint that can print a single (key, item) pair.
 * We print:
 *   nothing, if NULL fp.
 *   "(null)" if NULL ht.
 *   one line per hash slot, with no items, if NULL itemprint.
 *   otherwise, one line per hash slot, listing (key,item) pairs in that slot.
 * Note:
 *   the hashtable and its contents are not changed by this function,
 */
void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)){
    if(fp != NULL){
        if(ht == NULL){
            fprintf(fp, "(null)");
        }
        else{
            for(int x = 0; x<ht->num_slots; x++){
                if(itemprint != NULL){
                    set_print(ht->table[x], fp, itemprint);
                }
                fprintf(fp, "\n");
            }
        }
    }
}

/**************** hashtable_iterate ****************/
/* Iterate over all items in the table; in undefined order.
 *
 * Caller provides:
 *   valid pointer to hashtable, 
 *   arbitrary void*arg pointer,
 *   itemfunc that can handle a single (key, item) pair.
 * We do:
 *   nothing, if ht==NULL or itemfunc==NULL.
 *   otherwise, call the itemfunc once for each item, with (arg, key, item).
 * Notes:
 *   the order in which hashtable items are handled is undefined.
 *   the hashtable and its contents are not changed by this function,
 *   but the itemfunc may change the contents of the item.
 */
void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item) ){
    if(ht != NULL && itemfunc != NULL){
        for(int x = 0; x<ht->num_slots; x++){
            set_iterate(ht->table[x], arg, itemfunc);
        }
    }
}

/**************** hashtable_delete ****************/
/* Delete hashtable, calling a delete function on each item.
 *
 * Caller provides:
 *   valid hashtable pointer,
 *   valid pointer to function that handles one item (may be NULL).
 * We do:
 *   if hashtable==NULL, do nothing.
 *   otherwise, unless itemfunc==NULL, call the itemfunc on each item.
 *   free all the key strings, and the hashtable itself.
 * Notes:
 *   We free the strings that represent key for each item, because 
 *   this module allocated that memory in hashtable_insert.
 */
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) ){
    if(ht != NULL){
        for(int x = 0; x<ht->num_slots; x++){
            set_delete(ht->table[x], itemdelete);
        }
        free(ht->table);
        free(ht);
    }

}
