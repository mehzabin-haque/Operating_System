#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

int readcount, writecount, count = 5;                   
sem_t rmutex, wmutex, readTry, resource; 
int numPr_Cs[10] = {1,2,3,4,5,6,7,8,9,10}; 

//READER
void *reader(void *numR){
    //<ENTRY Section>
    //readTry.P();  
    sem_wait(&readTry);             
    //rmutex.P();   
    sem_wait(&rmutex);              
    readcount++;                    
    if(readcount == 1){           
        //resource.P();             
        sem_wait(&resource);
    }         
    //rmutex.V();
    sem_post(&rmutex);               
    //readTry.V();  
    sem_post(&readTry);             

    //<CRITICAL Section>
    printf(" Reader %d is reading the value %d\n",(*((int* )numR)),count);

    //<EXIT Section>
    //rmutex.P() 
    sem_wait(&rmutex);                
    readcount-- ;                     
    if(readcount == 0){              
        //resource.V();   
        sem_post(&resource);          
    }            
              
    //rmutex.V();                  
    sem_post(&rmutex);
}

//WRITER
void *writer(void *numW){

    //<ENTRY Section>
    //wmutex.P();      
    sem_wait(&wmutex);            
    writecount++;                
    if(writecount == 1){
        //readTry.P();   
        sem_wait(&readTry);
    }       

    //wmutex.V();  
    sem_post(&wmutex);                
    //resource.P();    
    sem_post(&resource);   

    //<CRITICAL Section>
    count = count*2 ;
    printf(" Writer %d has updated the value to %d\n",(*((int* )numW)),count);
    //resource.V();                
    sem_post(&resource);

    //<EXIT Section>
    //wmutex.P();  
    sem_wait(&wmutex);                
    writecount--;                
    if(writecount == 0){
        //readTry.V();   
        sem_post(&readTry);
    }                  
    //wmutex.V();                  
    sem_post(&wmutex);    

}

int main(){

    pthread_t c_read[10],c_write[10];

    sem_init(&rmutex,0,1);
    sem_init(&wmutex,0,1);
    sem_init(&readTry,0,1);
    sem_init(&resource,0,1);

	for(int i=0;i<10;i++){
		pthread_create(&c_read[i],NULL,(void*)reader,(void*)&numPr_Cs[i]);
		pthread_create(&c_write[i],NULL,(void*)writer,(void*)&numPr_Cs[i]);
	}

    	for(int i = 0; i < 10; i++) {
        	pthread_join(c_read[i], NULL);
		    pthread_join(c_write[i], NULL);
    	}

    //pthread_mutex_destroy(&mutex);
    //sem_destroy(&write);

return 0;
}
