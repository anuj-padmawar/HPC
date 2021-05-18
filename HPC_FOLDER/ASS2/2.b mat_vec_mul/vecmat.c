
#include <stdio.h>
#include <pthread.h>
 
#define MAX 512
#define MAX_THREAD 4

int part = 0;
struct arg{
	int vect[MAX], mat[MAX][MAX], ans[MAX] ;
	int tid;
};

void* vectmult(void * obj1)
{
	struct arg * obj;
	obj = (struct arg *)obj1;
	int i, j;   
    	int thread_part = part++;
    	for (i = thread_part * (MAX / 4); i < (thread_part + 1) * (MAX / 4); i++)
	{
		for(j=0;j<MAX;j++){
			obj->ans[i] += obj->mat[i][j] * obj->vect[j];
		}
	}

}
 
int main()
{
 
    	int i, j;
	struct arg obj;

	pthread_t threads[MAX_THREAD];

	for(i=0;i<MAX;i++)
	{
		obj.vect[i] = 1;
		obj.ans[i] = 0;
		for(j=0;j<MAX;j++)
			obj.mat[i][j] = 1;
	}

    	for (i = 0; i < MAX_THREAD; i++)
	{
		obj.tid = i;	
        	pthread_create(&threads[i], NULL, vectmult, (void *)&obj);
	}
 
    
    	for (i = 0; i < MAX_THREAD; i++)
        	pthread_join(threads[i], NULL);
 
    

    for (i = 0; i < MAX; i++)
	printf("\t %d", obj.ans[i]);

 
    return 0;
}
