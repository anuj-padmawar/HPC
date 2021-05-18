#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>
#define arrsize 20
int main()
{
int a[arrsize],n,i;
//int sum=0;
//int sum1=0;
int max_val=0;
//int min_val=99;
clock_t t;

//Serial program
printf("\nSERIAL PROGRAM\n");

t=clock();
for(i=0;i<arrsize;i++)
{
a[i]=i;
}
for(i=0;i<arrsize;i++)
{
if(max_val<a[i])
{
max_val=a[i];
}

}
printf("\nMaximum value in the array:val = %d\n",max_val);

t=clock()-t;
double time_taken=((double)t)/CLOCKS_PER_SEC;
printf("\nserial time taken = %f\n",time_taken);



printf("\nPARALLEL PROGRAM\n");
#pragma omp parallel for default(none) shared(a) reduction(max:max_val)
for(i=0;i<arrsize;i++)
{
a[i]=i;
}
double start=omp_get_wtime();
printf("\nstart time = %f\n",start);
for(i=0;i<arrsize;i++)
{
if(max_val<a[i])
{
max_val=a[i];
}
}
printf("\nMaximum value in the array:val = %d\n",max_val);
double end=omp_get_wtime();
double time;
time=end-start;
printf("\nEnd time = %f\n",end);
printf("\nTotal time required = %f\n",time);

return 0;
}


