#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h> 

#define NTHREADS 64;

int colors[64][64*3];

int x = 0;

void *myThreadFun(void *vargp) { 

   
   int i;
   for(i = 0; i < 64 * 3; i++){
	
    
	if ( i % 2 == 0){
		colors[x][i] = 133;
	}    
	else{
         colors[x][i] = i;
        }   
   }
  pthread_exit(NULL);

}

int main() 
{ 


//    pthread_t tid[NTHREADS];
    pthread_t tid; 
    printf("Before Thread\n"); 
    int i;
    for (i = 0; i < 64; i++){
    pthread_create(&tid, NULL, myThreadFun, (void*)&tid); 
    pthread_join(tid, NULL);
    x +=1;
        
	} 
    printf("After Thread\n"); 

        FILE *fp;
        fp = fopen("vthreads.ppm","w+");
        fputs("P3\n",fp);
        fputs("64 64\n",fp);
        fputs("255\n",fp);
        
        int j;
        for(i = 0; i < 64;i++){
                for(j = 0; j < 64*3; j++){
			 

                        fprintf(fp,"%d",colors[i][j]);
                        fputs(" ",fp);
                }
                fputs("\n",fp);

        }
        fclose(fp);
    
return 0;
}
