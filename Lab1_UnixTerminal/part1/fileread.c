// Compile with: gcc fileread.c -o fileread
// Run with: ./fileread

// Fill in the code!
//
//
#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE* myFile;

    myFile = fopen("./data.txt","r");


    if(NULL == myFile){
        fprintf(stderr,"data.txt not found, did you run data.sh?");
        fprintf(stderr,"note: stderr argument means we write to a special 'error' output stream.");
        fprintf(stderr,"Program terminating now...");
        exit(1);
    }

    char buffer[255];

     while(fscanf(myFile, "%s", buffer) != EOF){
        printf("Red Sox wins are: %s\n",buffer);
    }

    fclose(myFile);

   return 0;
}
