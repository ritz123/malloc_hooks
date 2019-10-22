#include <mcheck.h>
#include <stdlib.h>
#include <stdio.h>


void func1(void) {
  int j;
  for (j = 0; j < 2; j++)
    malloc(100);            /* Never freed--a memory leak */

  calloc(16, 16);             /* Never freed--a memory leak */
}

int
main(int argc, char *argv[])
{
  

  mtrace();
  
  
  func1();
  getchar();
  exit(EXIT_SUCCESS);
}