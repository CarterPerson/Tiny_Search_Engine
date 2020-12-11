## Carter Person, May 15th


This was implemented using an index object, as described in design.md. I verified the inputs from the command line, and passed them into a secondary function. In this function, an index object is created. The function then enters a loop, where it continuously goes up through file IDs, adding them to the index object, until it runs into an ID that does not exist. At this point, it then leaves the loop, writes all the information from the index object into the output file, and then deletes the index object.


The writing of the information from the webpage files into the index object involves a few steps. First, the file is read back into a webpage object. The webpage object then has a function that allows iteration through the html, where it progressively returns the next word on the webpage. By making use of this function, each word on the webpage is looked at and inserted into the index object. This functionality will read in all of the words from a single webpage, and as this is then used for each file in the directory that is passed into the main function, it will read in all of the files from the crawler's output directory.


The writing of this object makes use of a the hashtable_write and counters_write functions. As both of these are already written, Hashtable_write is called on the hashtable object stored in the index structure. The function that is passed into it has a slight addition ontop of the counters_write function, as it also writes the key (word) that is associated with the counter. By writing the key (word) followed by using the counter_write function for each counter stored in the hashtable, all of the information is written into the output file.