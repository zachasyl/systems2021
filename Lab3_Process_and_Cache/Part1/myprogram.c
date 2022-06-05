// Take a look at some of the previous examples to create your own program!
//
//
//


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){

	char* myargv[16];
	char* myargv2[16];
	char* myargv3[16];	
	myargv[0]="/bin/ls";
		
	
        myargv[1] = NULL;
        
	myargv2[0]="/bin/cat";
	myargv2[1] = "-n";
	myargv2[2] = "cat.txt";
	myargv2[3] = NULL;


	myargv3[0]="/bin/pwd";
        myargv3[1] = NULL;
	
	int i = 0;
		if(fork() == 0){
			
			execve(myargv[0],myargv,NULL);
			
			exit(1);	
		}
		if (fork() == 0){


                 execve(myargv3[0],myargv3,NULL);
			exit(1);	
                        }


		else{
		//children before this.		 

			wait(NULL);
			wait(NULL);
			execve(myargv2[0],myargv2,NULL);	 
			
			 
			printf("This always prints last\n");
			
			
	
		}
	
	return 0;

}
