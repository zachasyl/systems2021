#include <stdio.h>
#include<stdlib.h>
#include <ctype.h>


int main (int argc, char *argv[]) {

FILE* myFile;

// myFile will be the argv[1] argument (barebones.s or whatever file)
myFile = fopen(argv[1], "r"); 

// 9 strings max length of 7
	char instruction[9][7] = {
                      	 "addq", //0
                         "subq", //1
                         "mulq", //2
			 "movq",//3
			 "leaq",  //4
			 "pushq",//5
		         "popq",//6
			 "retq", //7
			 "divq" //8
	};
	int instructionSize = sizeof(instruction);


	//Cycle amounts from Agner Fog's page 10
	int cycles[9] = {
		1, //addq
		1, //subq
		3, //mulq
		1, //movq
		2, //leaq
		2, //pushq
		4, //popq
		2, //retq
		47 //divq		
	};

// this array will store the amount of times each instruction is found where for instance
// count[0] = 3 would mean that addq was found 3 times.
// the array starts with all values equaling 0.
	int count[9] = {0};

    
	if(NULL == myFile){
        	fprintf(stderr,"data.txt not found, did you run data.sh?");
        	exit(1);
    	}

	  // If we have successfully opened our file, we can now read each line.
          // We will read each line, until we reach the end of the file (EOF).
          char buffer[10]; // each word 10 chars at most we will say
          // So we will now take each word from a file(fscanf),
          // and store it as a character string(%s) in buffer each iteration.
                     
      	  int totalInstructions = 0;       
          while(fscanf(myFile, "%s", buffer) != EOF){
	  	int i = 0;
		int c = 0;	
		// this while loop will compare each buffer to each instruction.
		// i is set to 0 again in the fscan loop so that for each buffer i will start at 0			
		while(i < instructionSize){
			// using strcasecmp instead of strcmp should ignore capitalizations
			//strcmp compares the buffer with the instruction +i and returns 0 if they are equivalent
			
			int result = strcasecmp(buffer, instruction + i);
				
                         if (result == 0){
                               
			  	count[i] += 1;
				totalInstructions +=1;
			 }
			 i++;
		}		   
	 }
	 
	 int g = 0;
	 int totalCycles = 0;
	 // total cycles is calculated by multiplying the counts for each buffer with its cycle amt.
  	 for (g; g < 8; g++){
	 	printf("%s", instruction + g);
    		printf(": %d\n", count[g]);
		totalCycles +=  (count[g] * cycles[g]);
					
	}
	printf("Total Instructions: %d\n", totalInstructions);
	printf("Total Cycles: %d", totalCycles);
        // close our file
                                            
        fclose(myFile);
        return 0;
}
   

