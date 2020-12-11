#include <stdio.h>
#include <index.h>

int main(int argc, char *argv[]){
    if(argv != 3){
        printf("wrong argument number, please insert a file to draw from and a file to push into");
        return 1;
    }

    FILE *out = fopen(argv[2], "w");
    if( out == NULL){
        printf("bad destination file, please insert a valid destination");
        return 2;
    }

    index_t checker = index_ReadIndexFile(argv[1]);
    index_write(checker, out);
    fclose(out);

    return 0;


}




