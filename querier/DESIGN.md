## Author: Carter Person, May 24th

# High level design of Querier

1. first, this function breaks down the command lines inputs and makes sure that all of the input values are valid. This function then passes it into a "runner" function.
2. In this "runner" function, a few, high-level functions are called. The first of these is split line.
3. Split lines the line that is written by the user, and divides it into an array of multiple words, stored in a char **.
4. Next, the char ** produced by the split line function is is given to the scoring function along with the index structure given as a file in the command line.
5. In this, scoring will be done by taking the counters structures in the index for each word found from the query line. These will then be combined to create the "scores" for each sequence of "and"s and then combined over the different "or"s. The end result will be returned as a counters structure.
6. This final counters structure that represents ID-score pairs will be passed into a printing function, which will then iterate over the counters multiple times, printing the info for the highest value found each iteration, and then setting that value to zero. This will be done until all values are 0.