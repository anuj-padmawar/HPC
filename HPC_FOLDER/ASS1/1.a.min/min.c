#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>
#define arrsize 20
int main()
{
int a[arrsize],n,i;
int min_val=99;
clock_t t;

//Serial program
printf("SERIAL PROGRAM\n");

t=clock();
for(i=0;i<arrsize;i++)
{
a[i]=i+2;
}
for(i=0;i<arrsize;i++)
{
if(min_val>a[i])
{
min_val=a[i];
}

}
printf("\nMinimum value in the array:val = %d\n",min_val);

t=clock()-t;
double time_taken=((double)t)/CLOCKS_PER_SEC;
printf("\nTotal serial time required = %f\n",time_taken);


//parallel prgm
printf("\nPARALLEL PROGRAM\n");
#pragma omp parallel for default(none) shared(a) reduction(min:min_val)
for(i=0;i<arrsize;i++)
{
a[i]=i+2;
}
double start=omp_get_wtime();
printf("\nstart time = %f\n",start);
for(i=0;i<arrsize;i++)
{
if(min_val>a[i])
{
min_val=a[i];
}
}
printf("\nMinimum value in the array:val = %d\n",min_val);



double end=omp_get_wtime();
double time;
time=end-start;
printf("\nEnd time = %f\n",end);
printf("\nTotal Parallel time required = %f\n",time);
printf("\n");
return 0;
}


