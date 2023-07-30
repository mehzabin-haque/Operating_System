#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>

int mat[3][100000],count;
pthread_t thr[3];
sem_t lock;

void* countNum(void* num){
    int r = *(int*)num;

    sem_wait(&lock);

	for(int i=0;i<100000;i++){
		if(mat[r][i] == 1){
		       	count++;	
		}
	}
    
    sem_post(&lock);
}

int main(){

    for(int i=0;i<3;i++){
        for(int j=0;j<100000;j++){
            mat[i][j] = 1;
        }
    }

    sem_init(&lock, 0, 1);

    clock_t begin_time = clock();
    for(int i=0;i<3;i++){
        int* s = (int*)malloc(sizeof(int));
        *s = i;
		pthread_create(&thr[i], NULL, countNum, (void*)s);
    }

    for(int i=0;i<3;i++){
        pthread_join(thr[i],NULL);
    }

    clock_t end_time = clock();

    printf("Num of 1's (Synchronization) : %d Time = %.2lf \n",count, (double)(end_time-begin_time)/CLOCKS_PER_SEC);
}
