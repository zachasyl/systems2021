// Write a C program called array2.c that has an array of 400 integers in the function of main that is dynamically allocated.
//
//
#include <stdio.h> 
#include <stdlib.h> 
int main() 
{ 

	int* array;

	array = (int *)malloc(sizeof(int)*400);      

	array[66]=712;

	array[67]=719;

	array[300]=27;
	printf("%d\n", array[67]);
	return 0;
}
