## Carter Person May 16th

## Testing

For testing, I constructed an index object from a directory constructed by the crawler function. I did not include the test directory that I used while testing, however it can easily be generated by a crawler call. After reading through this directory and constructing an index structure for it, I wrote the index structure into the output file, following the format given by the guidelines. I then proceeded to delete the index object.


I then created a new index object, and used the index_readindexfile command to read the information held in the file created by the former index file into the new index file. After reading in that index file, I wrote the index_t * that it returned into a new file, named testoutCheck. If my reading and writing of index files worked properly, both of the files that hold the information of index structures should contain the same information (this would mean that all the information was preserved during the reading from an index file and during the writing into an index file). I then organized both of the index files using the indexsort_awk script provided, and compared the two files to see whether or not they were the same.


The result of the compare command is written into the file testingout. a value of 0 means that the two files hold the same exact data, which means that the reading and writing of index files preserves all of the information held.