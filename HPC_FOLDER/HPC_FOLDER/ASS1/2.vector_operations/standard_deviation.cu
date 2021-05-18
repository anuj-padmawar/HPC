#include<stdio.h>
#include<cuda.h>
#include<cuda_runtime.h>
#include<time.h>
__global__ void vecAdd(double *a,double *b,double *c,int n)
{
int id=blockIdx.x*blockDim.x+threadIdx.x;
if(id<n)
c[id]=a[id]+b[id];
}
int main()
{
srand(time(NULL));
double *h_a,*h_b,*h_c;
double *d_a,*d_b,*d_c;
int n=50;
int i=0;
clock_t t;

size_t bytes=n*sizeof(double);

h_a=(double*)malloc(bytes);
h_b=(double*)malloc(bytes);
h_c=(double*)malloc(bytes);

cudaMalloc(&d_a,bytes);
cudaMalloc(&d_b,bytes);
cudaMalloc(&d_c,bytes);
t=clock();
for(i=0;i<n;i++)
{
h_a[i]=i;
h_b[i]=i;
}

cudaMemcpy(d_a,h_a,bytes,cudaMemcpyHostToDevice);
cudaMemcpy(d_b,h_b,bytes,cudaMemcpyHostToDevice);

int blksize,gridsize;
blksize=50;
gridsize=(int)ceil((float)n/blksize);

vecAdd<<<gridsize,blksize>>>(d_a,d_b,d_c,n);

cudaMemcpy(h_c,d_c,bytes,cudaMemcpyDeviceToHost);
t=clock()-t;
double time_taken=((double)t)/CLOCKS_PER_SEC;
double sum=0;
for(i=0;i<n;i++)
sum+=h_c[i];

double mean=sum/n;
double temp=0;
for(i=0;i<n;i++)
{
temp+=(h_c[i]-mean)*(h_c[i]-mean);
}
double sd=temp/n;
printf("\nAddition=%f",sum);
printf("\nAverage=%f",mean);
printf("\nSD=%f \n",sd);
 printf("\n time taken to calculate max=%f",time_taken);
cudaFree(d_a);
cudaFree(d_b);
cudaFree(d_c);

free(h_a);
free(h_b);
free(h_c);

return(0);
}
