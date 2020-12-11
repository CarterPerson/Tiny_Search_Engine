# Carter Person, May 15th


## Compiling

call "make" while in the indexer directory


## Usage

This function takes 2 inputs, and can be used from the command line.

1. A directory that's contents have been produced by the crawler function
2. An output file where the index object created from the webpage files will be stored

ex. ./indexer testdir testout


## Assumptions:

1. Many of the functions that accomplish specific actions to accomplish the greater purpose of the indexer function call are designed only for internal use. In this, it is assumed that all of their inputs have already been checked and that the functions are being used correctly, and therefore these functions will not check to make sure all of the inputs are correct and will work.
2. automatically initializes the number of slots in hte hashtable to be 200. This is optimized at a usage of 40,000 unique words. Most datasets that we are working with in this class will not have that many unique words, but larger datasets will likely have close to it.

