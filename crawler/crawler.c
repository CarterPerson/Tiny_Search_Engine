
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagedir.h"
#include "bag.h"
#include "hashtable.h"
#include "webpage.h"

void crawl(char *url, char *dir, int *depth);

int main(int argc, char *argv[]){

	if(argc != 4){
		printf("wrong number of arguments. Please enter a seed Url, a directory where downloaded page files will be written, and a depth to which you would like to search /n");
		return 1; //means that there is the wrong number of variables
	}

	int *depth = calloc(1,sizeof(int *));
	*depth = 0;
	if(sscanf(argv[3], "%d", depth) == 0){
		printf("error with the third input, please make sure that its an integer value \n");
		free(depth);
		return 2; //means that the depth input was not a number value
	}

	char *url = argv[1];
	if(!(IsInternalURL(url))){
		printf("the supplied url is not an internal url, please make sure the url is valid and inside the dartmouth domain \n");
		free(depth);
		return 3; //means that the url is not valid/internal
	}

	//Tests to see whether the directory passed in is valid
	FILE *test;
	char *testfileName = calloc(strlen(argv[2])+10,sizeof(char));
	strcpy(testfileName,argv[2]);
	strcat(testfileName,"/.crawler");
	if((test = (FILE *)fopen(testfileName, "w")) == NULL){
		printf("directory is not a valid directory. Please insert a path to an existing, writeable directory \n");
		free(depth);
		free(testfileName);
		return 4; //invalid directory
	}
	else{
		free(testfileName);
		fclose(test);
	}
	
	//starts the web crawling
	crawl(url, argv[2], depth);
	free(depth);

	return 0;

}

//assumes the inputs are valid and the url is already normalized
void crawl(char *url, char *dir, int *depth){
	bag_t *toCrawl = bag_new(); //keeps a stack of urls that need to be searched
	hashtable_t *searched = hashtable_new(200); //tracks urls that have already been searched to avoid repeating
	char *str = calloc(strlen(url)+1, sizeof(char));
	strcpy(str,url);

	webpage_t *seed = webpage_new(str, 0, NULL); //original page to start the crawler with

	bag_insert(toCrawl, seed);
	hashtable_insert(searched, url, " ");
	webpage_t *curr;
	int id = 0;
	while((curr = (webpage_t *)bag_extract(toCrawl)) != NULL){
		id++;
		if(pagefetcher(curr)){
			pagesaver(curr, id, dir);
			if((webpage_getDepth(curr)) < *depth){
				pagescanner(toCrawl, searched, curr);
			}
		}
		webpage_delete(curr);
	}
	hashtable_delete(searched, NULL);
	bag_delete(toCrawl, webpage_delete);

}
