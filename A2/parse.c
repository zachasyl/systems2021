// Implement a working parser in this file that splits text into individual tokens.
//
//

#include <stdio.h>
#include <string.h>
int main (int argc, char *argv[]) {
  
  char *p;
  printf ("String  \"%s\" is split into tokens:\n", argv[1]);
  p = strtok (argv[1]," ");
  while (p!= NULL)
  {
    printf ("%s\n",p);
    p = strtok (NULL, " ");
  }
  return 0;
}
