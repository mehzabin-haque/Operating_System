#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

int readCount=5,readNum=0;
sem_t write;
pthread_mutex_t mutex;
int numPr_Cs[10] = {1,2,3,4,5,6,7,8,9,10}; 

void *writer(void *numW){
 sem_wait(&write);
 readCount = readCount*2;
 printf(" Writer %d has updated the value to %d\n",(*((int* )numW)),readCount);
 sem_post(&write);
}

void *reader(void *numR){
 pthread_mutex_lock(&mutex);
 readNum++;
 if(readNum == 1){
 	sem_wait(&write);
 }
 
 pthread_mutex_unlock(&mutex);
 printf(" Reader %d reading the value %d\n",(*((int* )numR)),readCount);
 pthread_mutex_lock(&mutex);
 readNum--;
 
 if(readNum == 0){
 	sem_post(&write);
 }
 
 pthread_mutex_unlock(&mutex);

}

int main(){
	pthread_t c_read[10],c_write[10];
    	pthread_mutex_init(&mutex, NULL);
    	sem_init(&write,0,1);

	for(int i=0;i<10;i++){
		pthread_create(&c_read[i],NULL,(void*)reader,(void*)&numPr_Cs[i]);
		pthread_create(&c_write[i],NULL,(void*)writer,(void*)&numPr_Cs[i]);
	}

    	for(int i = 0; i < 10; i++) {
        	pthread_join(c_read[i], NULL);
		pthread_join(c_write[i], NULL);
    	}

    pthread_mutex_destroy(&mutex);
    sem_destroy(&write);

return 0;
}
