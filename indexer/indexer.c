
#include "index.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void indexer(char *takedir, FILE *target);

int main(int argc, char *argv[]) {

    // Checks for the right number of arguments
    if(argc != 3){
        printf("Wrong number of arguments, please enter a directory produced by crawler and a target file as parameters \n");
        return 1;
    }

    //Tests to see whether the directory passed in is valid
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

    //Tests that the second argument can be opened as a writeable file
    FILE *target;
    if((target = (FILE *)fopen(argv[2], "w")) == NULL){
        printf("target file failed to be opened. Please make sure that target location has writing permissions \n");
        return 3; // invalid target location
    }

    //inputs have been checked and a write file has been successfully opened
    indexer(argv[1], target);

    
    fclose(target);

    // Testing code starts here
    index_t *tester = index_ReadIndexFile(argv[2]);
    FILE *testout = fopen("testoutCheck", "w");
    index_write(tester, testout);
    index_delete(tester);
    fclose(testout);
    // Testing code ends here


    
   
    return 0;

}


// Now that inputs have been verified, they are passed to this function to execute the actual command
void indexer(char *takedir, FILE *target) {

    index_t *index = index_New(300);
    int docID = 1;
    while( index_ReadInWebPage(index, takedir, docID)){
        docID++;
    }

    index_write(index, target);

    index_delete(index);

}






