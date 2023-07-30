#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
 
#define N 5
#define think 2
#define hungry 1
#define eat 0
#define right (pflag + 1) % N
#define left (pflag + 4) % N

 
int work[N];
int phil[N] = { 0, 1, 2, 3, 4 };
 
sem_t mutex;
sem_t S[N];
 
void eat_func(int pflag){

    if ((work[pflag] == hungry) && (work[left] != eat)&& (work[right] != eat)){
        work[pflag] = eat;
 
        printf("Philosopher %d takes fork %d and %d\n",pflag + 1, left + 1, pflag + 1);
        printf("Philosopher %d is eating\n", pflag + 1);

        sem_post(&S[pflag]);
    }
}
 
void take_chopsticks(int pflag){
 
    sem_wait(&mutex);
    work[pflag] = hungry;
 
    printf("Philosopher %d is hungry\n", pflag + 1);
    eat_func(pflag);
 
    sem_post(&mutex);
    sem_wait(&S[pflag]);
}

void drop_chopsticks(int pflag){

    sem_wait(&mutex);

    work[pflag] = think;
 
    printf("Philosopher %d putting fork %d and %d down\n",pflag + 1, left + 1, pflag + 1);
    printf("Philosopher %d is thinking\n", pflag + 1);
 
    eat_func(left);
    eat_func(right);
 
    sem_post(&mutex);
}
 
void* philosopher(void* num){
    int c=0;
 
    while (1) {
 
        int* i = num;
        take_chopsticks(*i);
        drop_chopsticks(*i);

        c++;
        if(c>5){
            break;
        }

    }
}
 
int main(){

    int i;
    pthread_t thread_id[N];
    sem_init(&mutex, 0, 1);
 
    for (i = 0; i < N; i++){
        sem_init(&S[i], 0, 0);
    }

    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL,philosopher, &phil[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }
 
    for (i = 0; i < N; i++){
        pthread_join(thread_id[i], NULL);
    }
       
}
