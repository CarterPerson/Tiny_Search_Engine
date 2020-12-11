/*Written by Carter Person */


#include <stdio.h>
#include "webpage.h"
#include "bag.h"
#include "hashtable.h"


/* pagefetcher
This function will call the fetch_page function from the webpage file on the page that is passed in.

It is assumed inside this function that all the parameters are in the correct format, as it is only
intended for internal use.
*/
bool pagefetcher(webpage_t *page);


/* pagesaver
This function will take a page, an integer fileID, and a target directory.

This function will assume that all inputs are in the correct form.

This function will create a file appropriately named in the target directory 
(file name will be a number that is incremented for each file), 
and then it will fill said file with all of required data.
    1. the url of the webpage
    2. the depth at which this webpage exists
    3. the html code for this webpage
*/
void pagesaver(webpage_t *page, int id, char *dir);


/* file2page
This function will read a file that has been written by pagesaver back into a webpage */
webpage_t *file2page(FILE *read);


/* pagescanner
This function will take a bag, a hastable of urls, and a webpage

This function will assume that all of the inputs are valid and in the correct format, as it 
is only intended for internal use

This function will scan the webpage for urls, and progressively create new webpages and add them to 
the bag, assuming that their url does not exist in the hashtable. Once added to the bag, the page's 
url will be added to the hastable as a key, to prevent it being repeated.
*/
void pagescanner(bag_t *pages, hashtable_t *urls, webpage_t *page);

