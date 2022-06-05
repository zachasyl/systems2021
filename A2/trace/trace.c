#include <stdio.h>

static int count = 0;

__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *this_fn, void *call_site){
        count++; 
	printf("Function entered\n");
}



__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *this_fn, void *call_site){
	printf("Function exited\n");		
	printf("Total Functions Called: %d\n", count);
}

	

