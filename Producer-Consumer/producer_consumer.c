#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t full,empty;
pthread_mutex_t mutex;
int buffer[5];
int in=0,out=0;

void *producer(void *pno){

   int item;
   for(int i=0; i<5;i++){
    item=rand();
    buffer[in]=item;
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    printf("%d no producer produced %d item at %d th place of buffer\n", *((int *)pno),buffer[in],in);
    in=(in+1)%5;
    sem_post(&empty);
    pthread_mutex_unlock(&mutex);
   }

}

void *consumer(void *cno){
    for(int i=0;i<5;i++){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item= buffer[out];
        printf("%d no consumer removed %d item from %d th place of buffer\n", *((int *)cno), buffer[in], in);
        out=(out+1)%5;
        sem_post(&full);
    pthread_mutex_unlock(&mutex);
        }
}

int main()
{
    sem_init(&empty,0,5);
    sem_init(&full,0,0);
    pthread_mutex_init(&mutex,NULL);
     
      pthread_t pro[5],con[5];

    int a[5]={1,2,3,4,5};

    for(int i=0;i<5;i++){
        pthread_create(&pro[i],NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i=0;i<5;i++){
        pthread_create(&con[i],NULL, (void *)consumer, (void *)&a[i]);
    }
    
        for(int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
 
}
