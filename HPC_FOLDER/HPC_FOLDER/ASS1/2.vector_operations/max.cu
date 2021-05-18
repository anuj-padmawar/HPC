#include <cuda.h>
#include <stdio.h>
#include <time.h>
#include<math.h>
#define TPB 512
#define SIZE 2048

    __global__ void max(int *a , int *c)	// kernel function definition
    {
    	int i = blockIdx.x * blockDim.x + threadIdx.x;	// initialize i to thread ID
	a[2*i] > a[2*i+1]? c[i] = a[2*i]:c[i] = a[2*i+1];
    }

    int main()
    {
    int i;
    srand(time(NULL));  //makes use of the computer's internal clock to control the choice of the seed

    int a[SIZE];
   // int c[SIZE];

    int *dev_a, *dev_c;   //GPU / device parameters

    cudaMalloc((void **) &dev_a, SIZE*sizeof(int));      //assign memory to parameters on GPU
    cudaMalloc((void **) &dev_c, SIZE*sizeof(int));

    for( i = 0 ; i < SIZE ; i++)
    {
    	a[i] = SIZE - i; // rand()% 1000 + 1;      // input the numbers
    }
   
        //copy the array from CPU to GPU
	
	for(i=1;i<log2((double)SIZE); i++)    
	{
		cudaMemcpy(dev_a , a, SIZE*sizeof(int),cudaMemcpyHostToDevice); 	
		max<<<1,SIZE/pow(2,i)>>>(dev_a,dev_c);
									// call kernel function <<<number of blocks, number of threads
    		cudaMemcpy(&a, dev_c, SIZE*sizeof(int),cudaMemcpyDeviceToHost);		// copy the result back from GPU to CPU
	}

	a[0] > a[1]? printf("\nMax: %d", a[0]): printf("\nMax: %d", a[1]);    
//	printf("\nmax =  %d ",a[0]);

    //cudaFree(dev_a);		// Free the allocated memory
    //cudaFree(dev_c);
  // printf("");

    return 0;
    }
