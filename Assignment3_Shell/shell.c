

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> // This is new!
#include <sys/types.h>
#include <sys/wait.h>

//max input.
# define BUFFER_SIZE 80

void sigint_handler(int sig){
	
	write(1,"Terminating through signal handler\n",35); 
	exit(0);
}


// This function contains three built-ins. It takes in the cmd[] to determine 
// which built-in to trigger. The mallocd history pointer array contains all commands user has entered.
// Exit is located elsewhere instead of returning a value from this fn  to trigger break it breaks from main,
void builtIn (char cmd[], char **history){
	
  //I should probably separate into further functions maybe use a switch malloc or call more fns and pass  but don't have the time
  // this was already very challenging.


	// built-in strings, looped through for help built-in.
	char builtIns[4][10] = {
                "help",
                "exit",
                "history",
                "cd"
        };
	char builtInsSummary[4][400] = {

                "lists available built-in commands.",
                "exits the shell. Bye!",
                "shows history of commands, last ten (will only show commands and command attempts, including built-ins, but not arguments).",
                "changes the directory."
        };

	// help
	int match = 1;		
        match = strncmp(cmd, "help", 10);
        if (match == 0 ){ //10 is max size to compare
                int theSize = sizeof(builtIns)/sizeof(builtIns[0]);
		int z = 0;
		for (z = 0; z < theSize; z++){
			printf("%s\n + %s\n" , builtIns[z], builtInsSummary[z]);
		} 
		return;	// will end here if condition was met.
	}

	//history
	 match = strncmp(cmd, "history", 10);
	 if (match ==0){
	 
              	int h = 0;
              	for (h = 0; h < 10; h++){
			if (history[h] != NULL){
                		printf("%s\n", history[h]);
			}
         	}	
		return;
	}
	//cd
	match = strncmp(cmd, "cd", 10);
        if (match ==0 ){
		chdir("..");
		return;
	}
	// will only print if there was no return.	
	printf("Command not found--Did you mean something else?\n");
		
	
}

int main () {

	// holds current string command after user inputs command or command and args.
	char cmd[100];

	// this variable will be incremented and never reset to 0. It is used for the history built-in function.
	int forever = 0;

	// history array pointer to hold each command input during course of running shell.
	char** history = malloc(sizeof(char) * 100);
        

	// Install our signal handler
        signal(SIGINT, sigint_handler);
        printf("You can only terminate by pressing Ctrl+C\n");
	
	// the main while loop that never stops.
  	while(1){
 
 		static int first_time = 1;
	        if (first_time){
                const char* CLEAR_SCREEN_ANSI = " \e[1;1H\e[2J";
                write(STDOUT_FILENO,CLEAR_SCREEN_ANSI,12);

                first_time = 0;
        }
	// printed before each user input
	printf("mini-shell>");

	char *array[100];
  	  
  	
	//pointer for input.
  	char *p;
	
	char input[BUFFER_SIZE];
        
     	char* par[20];
	
	// takes the stdin input and puts it into the input strring array.
	fgets(input, BUFFER_SIZE, stdin);
	
	// next use strtok on our input string to separate.
        p = strtok (input," \n");
	
	int i = 0;
	// 
        while (p!= NULL)
        {
        	// pointer to string added to our char array pointer
		// now each index has a different string.
                array[i++] = strdup(p);   
                p = strtok (NULL, " \n");
        	
        }
	  
	// copy first index, the command, to cmd string.
	strcpy(cmd, array[0]);
	// copy same to history.
	history[forever] = array[0];
	
	//increments so we can keep track of all commands for history fn.
	forever++;           
	
	int j = 0;
	for (j = 0; j < i; j++){ //since i is total.
		par[j] = array[j];
		par[i] = NULL; //terminator at end.

	}

	      i = 0;
  	      // exit functionality.
	      int toBreak = 1;
              toBreak = strncmp(cmd, "exit", 10);
              if (toBreak == 0){ //10 is max size to compare
              		break;
              }
	// calls other built-ins.
	builtIn(cmd, history);


	if(fork()==0){
		// Executes command from child then terminates our process	
       		execvp(cmd, par);
		
		
		exit(1);
	}else {
		
		wait(NULL); // This call makes the parent wait on its children.
	
              }		


	}
	return 0;
}
