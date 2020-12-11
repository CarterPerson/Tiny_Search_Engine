# Author: Carter Person, May 15th 2020

# Common

## pagedir

### usage

This file contains multiple helper functions that can be used when crawling the web. These include pagesaver, pagescanner, and pagefetcher.


### pagefetcher

This is a function that simply calls the webpage_fetch command to copy all of the html code from a website into a variable in a webpage structure. This function has a built in one second delay. This function takes a webpage object as an input.


### pagesaver

This function will take a page id (int), a target directory (char *), and a webpage as inputs. What this function will do it create a formatted file that contains the page's URL, depth, and html code. It will create this file in the target directory, and will name the file with the id.


### pagescanner

This function will scan over a page to check for urls within the html code. It takes a webpage, a pointer to a hashtable of URLs, and a pointer to a bag of webpages. As it runs through the webpages, It will turn valid urls into webpages and add them to the bag and adds the url to the url hashtable. the hastable ensures that no URLs are repeated, and the bag is a stack of webpages that still need to be processed.


### file2page

This function is designed to take the file that is written by pagesaver and essentially reverse it, reading the information inside of it back into a webpage structure. It takes a File pointer as an input, which needs to be a file written by pagesaver. It's output is a webpage pointer that has fully assigned values


## index


### Usage

This is an implementation of a hashtable with words as keys and counters as items. This is specifically catered for being implemented in a search engine, as it will break down how many time each word is used in each file.


### index_insert

This function will take an index, a word, and a document ID as inputs. It will use the counters_add function on the counter found at the word key. This should be used every time a word is encountered on a webpage to keep track of the proper wordcounts.


### index_insert_counters

This function is designed specifically for reading in from an index-printed file. It is designed to just put in a fully completed counter at a key for it's word.


### index_readin_webpage

This function is designed to go through a webpage object and read its data into an index object. It takes an index, and char * of the directory's name, and an int holding the documents ID. This function will adjust all of the counters' values to take account for the words it comes across while reading through the html.


### adjusted_print

This function is just a helper function that allows hashtable_print to be used. It matches the requested parameters of the helper function for hashtable_print, and implements a printing of the key of each counters, plus also counters_print.


### index_write

This function takes an index and a file pointer as inputs. This function will print the index into the given file.


### index_ReadIndexFile

This function takes a path name to a file, and reads the information in that file into an index object, which it then returns to the user.


### index_delete

This function will free up all memory currently being held by the index structure. It takes the index that you would like to delete as an input.


## word


### normalize

This function will take a char * as an input, and return the input, except fully lowercase.