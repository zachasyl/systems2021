// Write a C program that swaps two integers in a function
//
//
//
#include <stdio.h> 

void swap(long *a, long *b){
        long t0 = *a;
        long t1 = *b;
        *a = t1;
        *b = t0;

        printf("a = %d\n", *a);
        printf("b = %d\n", *b);
}


int main(){
        long a = 10;
        long b = 20;
        
        swap(&a, &b);
        return 0;
}

