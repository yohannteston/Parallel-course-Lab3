/**********************************************************************
 * Enumeration sort
 *
 **********************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int timer(void);

void print(double* a, int size){
	int i;
	for(i=0;i<size;i++)
		printf("%f ",a[i]);
	printf("\n");
}

int main(int argc, char *argv[]) {

  int len=50000,seed,i,j,rank;
  double *indata, *outdata,wtime;
  
  indata=(double *)malloc(len*sizeof(double));
  outdata=(double *)malloc(len*sizeof(double));

  /* Generate random numbers (Wichmann-Hill) */
  seed=171;
  for (i=0;i<len;i++){
    seed=(171*seed)%30269;
    indata[i]=seed/30268.0;
    outdata[i]=-1;
  }

  //print(indata,len);

  /* Enumeration sort */
  wtime=omp_get_wtime();

  omp_set_nested(1);

#pragma omp parallel for private(rank,i) 
  for (j=0;j<len;j++)
    {
	
	rank = 0;
#pragma omp parallel for reduction(+:rank) 
	for (i=0;i<len;i++)
		if (indata[i]<indata[j]) rank++;
      outdata[rank]=indata[j];
    }
  wtime=omp_get_wtime()-wtime;
  printf("Time: %f sec \n",wtime);

  /* Check results, -1 implies data same as the previous element */
    for (i=0; i<len-1; i++)
      if (outdata[i]>outdata[i+1] && outdata[i+1]>-1)
	printf("ERROR: %f,%f\n", outdata[i],outdata[i+1]);
    //print(outdata, len);

  return 0;
}
