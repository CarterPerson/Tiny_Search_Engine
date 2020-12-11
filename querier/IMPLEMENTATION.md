## Author: Carter Person, May 24th

# in depth design of Querier

1. first, this function breaks down the command lines inputs and makes sure that all of the input values are valid. This function then passes it into a "runner" function.
    1. First, the amount of arguments will be verified. 
    2. The directory will be verified by checking for the .crawler file inserted by the crawler function.
    3. The index file will be read into an index object. The creation of the index object will be verified, which means that the file offered had a valid path
2. In this "runner" function, a few, high-level functions are called. The first of these is split line.
3. Split lines the line that is written by the user, and divides it into an array of multiple words, stored in a char **.
    1.splitline will operate by creating a char ** object that has the maximum possible amount of "word slots" in it. This function will increment every time it steps off a character into whitespace, and turn all of the whitespaces into end of string characters. Whenever the function steps onto a new word, it will assign the pointer value for the start of that word to a slot in the char ** object. After iterating through the entire line and assigning all of the pointer values, I will add a "~" string to represent the end of the array of characters.
4. Next, the char ** produced by the split line function is is given to the scoring function along with the index structure given as a file in the command line.
5. In this, scoring will be done by taking the counters structures in the index for each word found from the query line. These will then be combined to create the "scores" for each sequence of "and"s and then combined over the different "or"s. The end result will be returned as a counters structure.
    1.These combinations will occur mostly through the use of the counters_iterate function. for "and"s that are encountered, This function, for each key in the second word's counter object in the index struct, will check and see if the value is smaller than the existing one in the first words. If it is, it will replace the first word's value with teh second word's
    2. by doing this, the whole "and sequence" up until the word being checked will be modeled as the "first word" as described, and the word being added will be modeled as the "second word" as it passes through the full "and sequence". This will successfully add the "second word" to whatever part of the "and sequence" that was iterated through before it.
    3. There is an exception for the first word of each "and sequence" where it basically acts like an "or" combine, with the initial counters object being an empty counters, which essentially copies that counters into what will represent the score for a full "and sequence".
    4. This "and" combination will then iterate through all keys in the older "and sequence" and set all of the keys that cannot be found in the counters word being added to zero. This is because that would mean that the ID represented by that key does not contain the new word and thus does not have a key to represent it, meaning that it is not iterated over in the counters_iterate function.
    5. The "or combine" function is a lot simpler. It simply adds all of the values from the new "word" or "and sequence" into the existing counters that represents the score.
    6.This function will combine these two by iterating over all of the "and sequences" and storing the pointer to the counters object that represents the total score of each and sequence. Only after calculating all of those scores will it run the "or combine" function through all of the seperate counters representing the individual "and sequence"s scores.
6. This final counters structure that represents ID-score pairs will be passed into a printing function, which will then iterate over the counters multiple times, printing the info for the highest value found each iteration, and then setting that value to zero. This will be done until all values are 0.
     1. As I need to keep track of multiple values, the standard counters_iterate won't work for this without creating a new structure, so I needed to use loops.
     2. This function finds finds the highest key value is the counters and uses this as the top value in a for loop.
     3. In this for loop, the highest "score" is found, and it as well as the document ID (key) that it is found at will be recorded
     4. This function then opens up the webpage file that corresponds to the document ID and copies its url. 
     5. This function then the score, document ID, and the url on a line with a new line character.
     6. The "score" for this page is then set to 0 to prevent it from being identified as the highest again.
     7. This is all nested in a while loop. As soon as the highest score found is 0, then this while loop will terminate, as this will mean that all webpages that match to any degree will have had their score, ID, and url printed.