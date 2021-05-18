
#include <stdio.h>
#include <pthread.h>
 
#define MAX 100
#define MAX_THREAD 4

int part = 0;
struct arg{
	int A[MAX], B[MAX], C[MAX] ;
};

void* vectmult(void * obj1)
{
	struct arg * obj;
	obj = (struct arg *)obj1;
	int i, j;   
    	int thread_part = part++;
    	for (i = thread_part * (MAX / 4); i < (thread_part + 1) * (MAX / 4); i++)
	{
		obj->C[i] = obj->A[i] + obj->B[i];	
	}

}
 
int main()
{
 
    	int i, j;
	struct arg obj;

	pthread_t threads[MAX_THREAD];

	for(i=0;i<MAX;i++)
	{
		obj.A[i] = 1;
		obj.B[i] = 1;
		obj.C[i] = 0;
	}

    	for (i = 0; i < MAX_THREAD; i++)
	{
        	pthread_create(&threads[i], NULL, vectmult, (void *)&obj);
	}
 
    
    	for (i = 0; i < MAX_THREAD; i++)
        	pthread_join(threads[i], NULL);
 
    

    for (i = 0; i < MAX; i++)
	printf("\t %d", obj.C[i]);
         printf("\n");
 
    return 0;
}
