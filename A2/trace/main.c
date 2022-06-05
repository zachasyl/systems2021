#include <stdio.h>
#include <time.h>


void msg(){
	printf("Hello!\n");
}


int main(){
	clock_t start_t, end_t, total_t;
	start_t = clock();	
	int i;
	for(i= 0;i  < 200000; ++i){
		msg();
	}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Time taken by CPU %d\n", total_t);

	return 0;
	
}
