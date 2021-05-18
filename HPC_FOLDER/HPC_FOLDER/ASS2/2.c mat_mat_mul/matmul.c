#include <stdio.h>
#include <pthread.h>
 
#define MAX 10
#define MAX_THREAD 4

int part = 0;
struct arg{
	int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX] ;
};

void* matmult(void * obj1)
{
	struct arg * obj;
	obj = (struct arg *)obj1;
		
	int i, j, k;   
    	int thread_part = part++;
    	for (i = thread_part * (MAX / 4); i < (thread_part + 1) * (MAX / 4); i++)
		for(j=0;j<MAX;j++)
			for(k=0;k<MAX;k++)			
				obj->C[i][j] += obj->A[i][k] * obj->B[k][j];
}
 
int main()
{
    	int i, j;
	struct arg obj;

	pthread_t threads[MAX_THREAD];

	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			obj.A[i][j] = 1;
			obj.B[i][j] = 1;
			obj.C[i][j] = 0;
		}
	}

    	for (i = 0; i < MAX_THREAD; i++)
	{
        	pthread_create(&threads[i], NULL, matmult, (void *)&obj);
	}
 
    
    	for (i = 0; i < MAX_THREAD; i++)
        	pthread_join(threads[i], NULL);
 
    

    	for (i=0;i<MAX;i++)
		for(j=0;j<MAX;j++)
			//printf("\t %d", obj.B[i][j]);
			printf("\t %d", obj.C[i][j]);

 
    	return 0;
}
