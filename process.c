#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<wait.h>
#include<signal.h>
#include<sys/wait.h>

void signal_handle(int signal){
  switch (signal) {
    case SIGINT: printf("PID %d %s\n",getpid(),"ready");
    case SIGBUS: printf("PID %d %s\n",getpid(),"caught one");
    case SIGKILL: printf("PID %d %s\n",getpid(),"dead");
  }
}

int main(){
// to create 5 process (include the source process), i actually create 4 childs
// for the 4 childrens create , i need to use in 2 times in fork().
// 2^x = childrens , when x is fork() calls.
pid_t pid;
// pid = fork();
// pid = fork();

size_t round = 0;

// create 5 process
pid = fork();
fork();
fork();

if(pid >= 0){  // fork success

if(pid > 0){ // Father case
  printf("PID %d %s\n",getpid(),"ready");
  while(round < 5){
  round++;
  signal(SIGINT,signal_handle); // ready case
  sleep(1);
 }
 printf("PID %d %s\n",getpid(),"caught one");
 while( round >= 5 && round < 10){
  round++;
  signal(SIGBUS,signal_handle); // ready case
  sleep(1);
 }
 printf("PID %d %s\n",getpid(),"dead");
 while(round >= 10 && round < 15){
  round++;
  signal(SIGKILL,signal_handle); // ready case
  sleep(1);
  }
}
  else if(pid == 0){ // Child case
    wait(NULL);
    if(round <= 5){
    kill(getpid(),SIGINT);
    signal_handle(SIGINT);
   }
   if(round > 5 && round <= 10){
     kill(getpid(),SIGBUS);
     signal_handle(SIGBUS);
   }
   if(round > 10 && round <= 15){
     kill(getpid(),SIGKILL);
     signal_handle(SIGKILL);
   }
   exit(1);

}//
}
else{ // failed
  printf("%s\n","fork() failed");
  exit(0);
}
return 0;
}
