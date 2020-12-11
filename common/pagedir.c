#include <stdio.h>
#include <stdlib.h>
#include "webpage.h"
#include "pagedir.h"
#include "bag.h"
#include "hashtable.h"
#include "file.h"
#include <string.h>



/* pagefetcher
This function will call the fetch_page function from the webpage file on the page that is passed in.

It is assumed inside this function that all the parameters are in the correct format, as it is only
intended for internal use.
*/
bool pagefetcher(webpage_t *page){
 return webpage_fetch(page);
}


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
void pagesaver(webpage_t *page, int id, char *dir){
    char *filename = calloc(strlen(dir)+(sizeof(id)/4)+2, sizeof(char));
    sprintf(filename, "%s/%d", dir, id);
    FILE *writer;
    if((writer = (FILE *)fopen(filename, "w")) != NULL){
        fprintf(writer, "%s\n", webpage_getURL(page));
        fprintf(writer, "%d\n", webpage_getDepth(page));
        fprintf(writer, "%s", webpage_getHTML(page));
        fclose(writer);
    }
    free(filename);
}



webpage_t *file2page(FILE *read){
    char *url;
    int *depth = calloc(1,sizeof(int));
    char *html;
    url = freadlinep(read);
    char *depthString = freadlinep(read);
    sscanf(depthString, "%d", depth);
    html = freadfilep(read);
    int depthin = *depth;
    free(depth);
    free(depthString);
    return webpage_new(url,depthin,html);
    
}

/* pagescanner
This function will take a bag, a hastable of urls, and a webpage

This function will assume that all of the inputs are valid and in the correct format, as it 
is only intended for internal use

This function will scan the webpage for urls, and progressively create new webpages and add them to 
the bag, assuming that their url does not exist in the hashtable. Once added to the bag, the page's 
url will be added to the hastable as a key, to prevent it being repeated.
*/
void pagescanner(bag_t *pages, hashtable_t *urls, webpage_t *page){
    int depth = webpage_getDepth(page);
    int *pos = calloc(1, sizeof(int *));
    char *currURL;
    while((currURL = webpage_getNextURL(page, pos)) != NULL){
        if(IsInternalURL(currURL)){
            if(hashtable_insert(urls, currURL, " ")){
                char *str = calloc(strlen(currURL)+1, sizeof(char));
                strcpy(str,currURL);
                webpage_t *temp = webpage_new(str, depth+1, NULL);
                bag_insert(pages,temp);
            }
        }
        free(currURL);
    }
    free(pos);
}
