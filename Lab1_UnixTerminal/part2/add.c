// Write a C program that calls an add function(long add(long a, long b).
//
//

#include <stdio.h>

int add(int a, int b){
	int c = a + b;
	return c;
}
int main () {

 add(5, 6);  
 printf("%d", add(5,6));
}

