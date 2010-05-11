/**********************************************************************
 * A simple "hello world" program for OpenMP/C
 *
 *
 **********************************************************************/

#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

  printf("Starting\n");
  printf("%d threads involved\n",omp_get_max_threads()); 
#pragma omp parallel 
  {
  printf("Thread %d: Hello World!\n",omp_get_thread_num()); 
  }

  printf("Stopping\n"); 

  return 0;
}
