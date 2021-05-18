#include<cuda.h>
#include<stdio.h>
#include<time.h>
#define SIZE 1000
__global__ void min(int *a,int *c)
{
int i = threadIdx.x;
*c = a[0];
        if(a[i] < *c)
             {
               *c = a[i];
             }
}
int main()
{
int i;
srand(time(NULL));

int a[SIZE];
int c;
int *dev_a, *dev_c;
cudaMalloc((void **) &dev_a, SIZE*sizeof(int));
cudaMalloc((void **) &dev_c, SIZE*sizeof(int));
for(i=0;i<SIZE;i++)
{
a[i] = i+8;
}
cudaMemcpy(dev_a,a, SIZE*sizeof(int),cudaMemcpyHostToDevice);
min<<<1,SIZE>>>(dev_a,dev_c);
cudaMemcpy(&c,dev_c,SIZE*sizeof(int),cudaMemcpyDeviceToHost);

printf("\nmin = %d ",c);
cudaFree(dev_a);
cudaFree(dev_c);;
return 0;
}

