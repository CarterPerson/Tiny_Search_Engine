#include "index.h"
#include <stdio.h>
#include <string.h>
#include "word.h"
#include "counters.h"
#include "file.h"

int runQuery(char *dirpath, index_t *index, char *inputline);
char **splitline(char *line);
counters_t *scorequery(index_t *index, char **words);
void scorecombineand(counters_t *andsequenceScores, counters_t *wordscores, bool first);
void scorecombineor(counters_t *scores, counters_t *andsequenceScores);
void words_delete(char **words, int slots);
void printqueryresults(char *dirpath, counters_t *scores);

int main(int argc, char *argv[]){

    //checks if the number of arguments is correct
    if(argc != 3){
        printf("wrong number of arguments, please insert the path of a directory made by crawler and an indexfile made by indexer\n");
        return 1;
    }

    //checks that the directory was generated by crawler
    FILE *test;
	char *testfileName = calloc(strlen(argv[1])+10,sizeof(char));
	strcpy(testfileName,argv[1]);
	strcat(testfileName,"/.crawler");
	if((test = (FILE *)fopen(testfileName, "r")) == NULL){
		printf("directory is not a valid directory. Please insert a path to an existing directory made by a crawler call \n");
		free(testfileName);
		return 2; //invalid directory
	}
	else{
		free(testfileName);
		fclose(test);
	}

    //reads in the index struct from the file provided
    index_t *index = index_ReadIndexFile(argv[2]);

    if(index == NULL){
        printf("invalid indexer-produced file\n");
        return 3;
    }

    //prompts the user for a query
    printf("Query?\n");
    char *inputline = freadlinep(stdin);

    //prints query for user to see
    printf("Query: %s\n", inputline);

    //normalizes the query provided by the user
    char *normalizedinput = normalize(inputline);
    free(inputline);


    runQuery(argv[1], index, normalizedinput);


    index_delete(index);
    free(normalizedinput);

    return 0;

}

//main runner function, abstract level detail for how the function runs
int runQuery(char *dirpath, index_t *index, char *inputline){

    char **words = splitline(inputline);
    counters_t *scores = scorequery(index, words);

    printqueryresults(dirpath, scores);
    
    counters_delete(scores);

    return 0;
}


//splits the line provided into an array of char *'s, with each pointer pointing to an individual word
//sets the final value of the array to  "~" to be able to recognize the end in another function
char **splitline(char *line){
    bool lastspace = true;
    int place = 0;
    char **words = calloc((strlen(line)/2 +2), sizeof(char *));
    while((*line) != '\0'){
        if((*line) == ' '){
            *line = '\0';
            if(lastspace == false){
                place++;
            }
            lastspace = true;
        }
        else{
            if(lastspace){
                words[place] = line;
                lastspace = false;
            }
        }
        line = line+1;
    }
    if(lastspace){
        words[place] = "~\0"; //using the ~ as an identifier of the end of the sequence
    }
    else{
        words[place+1] = "~\0";
    }
    return words;
}

//takes the split array of words as a char **, runs through it and combines scores
counters_t *scorequery(index_t *index, char **words){
    counters_t *scores = counters_new();
    bool first = true;
    int location = 0;
    counters_t **andsequences = calloc(10, sizeof(counters_t *));
    int andsequencecount = 0;
    while(strcmp("~", words[location]) != 0){
        counters_t *andsequenceScores = counters_new();
        while((strcmp("or", words[location]) != 0) && (strcmp("~", words[location]) != 0)){
            if(strcmp(words[location], "and") != 0){
                counters_t *wordscores = index_getCounter(index ,words[location]);
                scorecombineand(andsequenceScores, wordscores, first);
                first = false;
            }
            location++;
        }
        if((strcmp("~", words[location]) != 0)){
            location++;
        }
        andsequences[andsequencecount] = andsequenceScores;
        andsequencecount++;
        first = true;
    }
    int x = 0;
    while(andsequences[x] != NULL){
        scorecombineor(scores,andsequences[x]);
        counters_delete(andsequences[x]);
        x++;
    }
    free(andsequences);
    free(words);
    return scores;
}

//helper function for scorecombineand; to be used in a counters_iterate call. Combines scores
//by key-value pair
// NOTE: this does not perform elimination of keys that do not exist is the word's score.
//      Elmination will be performed in the second iterate function.
void combinehelperand1(void *andsequencecounters, const int key, const int value){
    int previous = counters_get(andsequencecounters, key);
    if(value<previous){
        counters_set(andsequencecounters, key, value);
    }
}

//gets the highest key value in a counters
void gethighest(void *highest, const int key, const int value){

    if(key > *((int *)highest)){
        *((int *)highest) = key;
    }
}

//helper function for scorecombineand; to be used in a counters_iterate call. Combines scores
//by key-value pair
void combinehelperor(void *scores, const int key, const int value){
    int newvalue = counters_get(scores, key) + value;
    counters_set(scores, key, newvalue);
}



//helper function for scorequery; takes the lowest, set value for each ID between the two input
//counters and sets that value in andsequenceScores
void scorecombineand(counters_t *andsequenceScores, counters_t *wordscores,bool first){
    if(first){ //for the first time its run (with an empty andsequencescores) it must act like an "or" combine
        counters_iterate(wordscores, andsequenceScores, combinehelperor);
    }
    else{ //after the first run, it should choose the lowest value for each key for each "and" sequence
        counters_iterate(wordscores, andsequenceScores, combinehelperand1);
        int *highest = calloc(1, sizeof(int)); //to be used in a limiting statement for a for-loop
        counters_iterate(andsequenceScores, highest, gethighest); //assigns a value to highest that correspond to the highest key in wordscores
        for(int x = 0; x<= *highest; x++){
            if(counters_get(wordscores, x) == 0){
                counters_set(andsequenceScores, x, 0); //sets values to 0 if not found in wordscores
            }
        }
        free(highest);

    }
}


//helper function for scorequery; adds the values for each ID from both counters, and sets that value in scores
void scorecombineor(counters_t *scores, counters_t *andsequenceScores){
    counters_iterate(andsequenceScores, scores, combinehelperor);
}



void printqueryresults(char *dirpath, counters_t *scores){

    int *highest = calloc(1, sizeof(int));
    counters_iterate(scores, highest, gethighest); //finds the highest key value to allow iteration that can change values
    int maxvalue = 1;
    int keymatch = 0;
    while(maxvalue > 0){
        maxvalue = 0;
        keymatch = 0;
        for(int x = 0; x<= *highest; x++){
            if(counters_get(scores, x) > maxvalue){
                maxvalue = counters_get(scores, x);
                keymatch = x;
            }
        }
        if(maxvalue > 0){
            FILE *read;
            char *IDnumber = calloc(8, sizeof(char)); //NOTE CHECK HERE
            sprintf(IDnumber, "%d", keymatch);
            char *path = calloc(strlen(dirpath)+strlen(IDnumber)+2, sizeof(char));
            strcpy(path, dirpath);
            strcat(path, "/");
            strcat(path, IDnumber);
            free(IDnumber);
            if((read = fopen(path, "r")) == NULL){
                free(path);
            }
            char *url;
            url = freadwordp(read);
            fclose(read);
            free(path);
            printf("document score: %d   ", counters_get(scores, keymatch));
            printf("document ID: %d   ", keymatch);
            printf("document url: %s\n", url);
            free(url);
            counters_set(scores, keymatch, 0);
        }
    }
    free(highest);
}

