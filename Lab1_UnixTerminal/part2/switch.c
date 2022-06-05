// Write a C program using a switch statement
//

#include <stdio.h>
 
int main () {

   /* local variable definition */
   char door = '3';

   switch(door) {
      case '1' :
         printf("Door 1 has 1 million dollars\n" );
         break;
      case '2' :
         printf("Door 2 has nothing.\n" );
         break;
      case '3' :
         printf("Door 3 has a toaster.\n" );
         break;
      
   }
   
   printf("%c", door);
 
   return 0;
}
