## Carter Person, May 15th

# Design

The purpose of indexer is to take a path to a directory that holds output files from the crawler function and an output destination, and then to essentially condense the information held the directory of webpage files into an object that is much easier to search through in a search engine. It is also designed to write this object into a file which can later be read back into an index object.


To start, the basis of this function is a structure called an index. This is an implementation of a hashtable, which has the keys as words it encounters and has counters as those key's values. These counters will use the document IDs to keep track of how many times each word occurs in each document.


The function will work by checking the inputs from the command line, then once it makes sure that the inputs are ok, transfers them into the actual function. This function will make an index object, then read each file from the directory that was passed into the function. This will give all of the information from that directory to the index object, which it will then reduce into just the information relevant for the index object.


After fully reading in all of the relevant information, this function will then write the index object into the output location that the user passed into this function. The index struct will also implement a reading function so that a file that is output by its writing function can be raed back into an index object whenever desired.