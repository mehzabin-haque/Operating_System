#include<stdio.h>
#include<unistd.h>
int main(){
int pid;
printf("I am the original process with PID %d and PPID %d.\n",getpid(),getppid());
pid = fork();
if(pid == 0){
printf("I am the child process with PID %d and PPID %d.\n",getpid(),getppid());}

else {
printf("I am the parent process with PID %d and PPID %d.\n",getpid(),getppid());
printf("My child's PID is %d\n",pid);
}

printf("\nPID %d terminates ",getpid() );
}
