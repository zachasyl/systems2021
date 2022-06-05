//
// Compile with: clang -lm trace.c -o trace
//
// Run with: ./trace
//
// This program generates a trace file(s) that represents
// addresses that get put into a cache.
//
//
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "binary.h"

// Toggle these values to generate different
// addresses
#define BITWIDTH 8	// Our architecture is an 8-bit architecture
#define ADDRESSES 1024	// We will generate 512 instructions
#define RANGE 256	// The range of these instructions is a value 0-32



// Generate a regular data access pattern
//
// params: 	size - How many addresses to generate
//		range - The range of addresses
void Trace(int size, int range){
	FILE* fp = fopen("regular.txt","w");

	for(int i=0; i < size; i++){
		char* bin=intToBinaryString((i%range),BITWIDTH);
		fprintf(fp,"%s\n",bin);
		free(bin);
	}

	fclose(fp);
}

// Generaet a random data access pattern
void randomTrace(int size, int range){
	FILE* fp = fopen("random.txt","w");

	srand(time(NULL));

	for(int i=0; i < size; i++){
		char* bin = intToBinaryString((rand()%range),BITWIDTH);
		fprintf(fp,"%s\n",bin);
		free(bin);
	}

	fclose(fp);
}

//Bad trace. start at 3 then add iterator +8 ie 11, 19, 27, 35. 1s and 2s place will always be 01 and so
//each binary in the txt would be added to the same place in the cache, constantly replacing it.
void badTrace(int size, int value){
	
	int iterator = 8;
	FILE* fp = fopen("bad.txt","w");
        srand(time(NULL));

        for(int i=0; i < size; i++){
		// resets to value(3) + 0 which is three, then 11, then 19 etc.
		if (iterator == 256){
			iterator = 0;
		}
                char* bin = intToBinaryString(value + iterator,BITWIDTH);
                fprintf(fp,"%s\n",bin);
                free(bin);
		
			iterator += 8;
		}
        

        fclose(fp);
}

//Same as singleTrace. Like badtrace the same cache location is solely targeted( since the 1s and 2s place must
//be the same since the value is always the same). But unlike badtrace, the number is always the same rather than different and so a hit is guaranteed.
void goodTrace(int size, int value){
        FILE* fp = fopen("good.txt","w");

        srand(time(NULL));

        for(int i=0; i < size; i++){
                char* bin = intToBinaryString(value,BITWIDTH);
                fprintf(fp,"%s\n",bin);
                free(bin);
        }

        fclose(fp);
}


// Generaetes a single value, over and over again.
// This is the most basic trace file.
void singleTrace(int size, int value){
	FILE* fp = fopen("single.txt","w");

	srand(time(NULL));

	for(int i=0; i < size; i++){
		char* bin = intToBinaryString(value,BITWIDTH);
		fprintf(fp,"%s\n",bin);
		free(bin);
	}

	fclose(fp);
}


// Generate a more realistic data access pattern
// This will generate addresses that may repeat over time
void realisticTrace(int size, int range){
	FILE* fp = fopen("realistic.txt","w");

	srand(time(NULL));


	for(int i=0; i < size;){

		int isJump = rand()%2;
		// If a jump does not occur, then just generate a random instruction
		// otherwise, generate a few instructions and repeat them all several times
		if (isJump==0){
			char* bin = intToBinaryString((rand()%range),BITWIDTH);
			fprintf(fp,"%s\n",bin);
			free(bin);
			++i;
		}else{
				
			char* bin1 = intToBinaryString((rand()%range),BITWIDTH);
			char* bin2 = intToBinaryString((rand()%range),BITWIDTH);
			char* bin3 = intToBinaryString((rand()%range),BITWIDTH);
			
			for(int j = 0; j < 10 && i < size; j++, i+=3){
				fprintf(fp,"%s\n",bin1);
				fprintf(fp,"%s\n",bin2);
				fprintf(fp,"%s\n",bin3);
			}
			
			free(bin1);
			free(bin2);
			free(bin3);
		}
	}

	fclose(fp);
}

int main(){

	Trace(ADDRESSES,RANGE);
	randomTrace(ADDRESSES,RANGE);
	realisticTrace(ADDRESSES,RANGE);
	singleTrace(ADDRESSES,42);
	badTrace(ADDRESSES,3);
	goodTrace(ADDRESSES, 10);
	// Some unit tests for the binary conversions if you want
	// to play around with larger sets.
	char* test1 = intToBinaryString(255,BITWIDTH);
	printf("Example: 255 = %s\n", test1);
	printf("Binary(0,0) of 255: %d\n",binaryStringRangeToInt(test1, 0, 0));
	printf("Binary(0,1) of 255: %d\n",binaryStringRangeToInt(test1, 0, 1));
	printf("Binary(0,2) of 255: %d\n",binaryStringRangeToInt(test1, 0, 2));
	printf("Binary(0,3) of 255: %d\n",binaryStringRangeToInt(test1, 0, 3));
	printf("Binary(0,4) of 255: %d\n",binaryStringRangeToInt(test1, 0, 4));
	printf("Binary(0,5) of 255: %d\n",binaryStringRangeToInt(test1, 0, 5));
	printf("Binary(0,6) of 255: %d\n",binaryStringRangeToInt(test1, 0, 6));
	printf("Binary(0,7) of 255: %d\n",binaryStringRangeToInt(test1, 0, 7));
	free(test1);


	char* test2 = intToBinaryString(0,BITWIDTH);
	printf("\nExample: 0 = %s\n", test2);
	printf("Binary(0,0) of 0: %d\n",binaryStringRangeToInt(test2, 0, 0));
	printf("Binary(1,1) of 0: %d\n",binaryStringRangeToInt(test2, 1, 1));
	printf("Binary(2,2) of 0: %d\n",binaryStringRangeToInt(test2, 2, 2));
	printf("Binary(3,3) of 0: %d\n",binaryStringRangeToInt(test2, 3, 3));
	printf("Binary(4,4) of 0: %d\n",binaryStringRangeToInt(test2, 4, 4));
	printf("Binary(5,5) of 0: %d\n",binaryStringRangeToInt(test2, 5, 5));
	printf("Binary(6,6) of 0: %d\n",binaryStringRangeToInt(test2, 6, 6));
	printf("Binary(7,7) of 0: %d\n",binaryStringRangeToInt(test2, 7, 7));
	free(test2);

	char* test3 = intToBinaryString(42,BITWIDTH);
	printf("\nExample: 42 = %s\n", test3);
	printf("Binary(0,0) of 42: %d\n",binaryStringRangeToInt(test3, 0, 0));
	printf("Binary(1,1) of 42: %d\n",binaryStringRangeToInt(test3, 1, 1));
	printf("Binary(2,2) of 42: %d\n",binaryStringRangeToInt(test3, 2, 2));
	printf("Binary(3,3) of 42: %d\n",binaryStringRangeToInt(test3, 3, 3));
	printf("Binary(4,4) of 42: %d\n",binaryStringRangeToInt(test3, 4, 4));
	printf("Binary(5,5) of 42: %d\n",binaryStringRangeToInt(test3, 5, 5));
	printf("Binary(6,6) of 42: %d\n",binaryStringRangeToInt(test3, 6, 6));
	printf("Binary(7,7) of 42: %d\n",binaryStringRangeToInt(test3, 7, 7));
	free(test3);
	

	char* test4 = intToBinaryString(81,BITWIDTH);
	printf("\nExample: 81 = %s\n", test4);
	printf("Binary(0,0) of 81: %d\n",binaryStringRangeToInt(test4, 0, 0));
	printf("Binary(0,1) of 81: %d\n",binaryStringRangeToInt(test4, 0, 1));
	printf("Binary(1,1) of 81: %d\n",binaryStringRangeToInt(test4, 1, 1));
	printf("Binary(1,2) of 81: %d\n",binaryStringRangeToInt(test4, 1, 2));
	printf("Binary(1,3) of 81: %d\n",binaryStringRangeToInt(test4, 1, 3));
	printf("Binary(2,5) of 81: %d\n",binaryStringRangeToInt(test4, 2, 5));
	printf("Binary(5,7) of 81: %d\n",binaryStringRangeToInt(test4, 5, 7));
	printf("Binary(6,7) of 81: %d\n",binaryStringRangeToInt(test4, 6, 7));
	printf("Binary(7,7) of 81: %d\n",binaryStringRangeToInt(test4, 7, 7));
	free(test4);

	return 0;
}
