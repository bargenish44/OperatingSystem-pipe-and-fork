#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<wait.h>
#include<signal.h>
#include<sys/wait.h>

#define SIGREADY 0
#define SIGCAUGHT 1
#define SIGDEAD 2

void signal_handle(int signal){
  switch (signal) {
    case SIGREADY: printf("PID %d %s\n",getpid(),"ready");
    case SIGCAUGHT: printf("PID %d %s\n",getpid(),"caught one");
    case SIGDEAD: printf("PID %d %s\n",getpid(),"dead");
  }
}


int main(){
// to create 5 process (include the source process), i actually create 4 childs
// for the 4 childrens create , i need to use in 2 times in fork().
// 2^x = childrens , when x is fork() calls.
pid_t pid;
pid = fork();
pid = fork();

size_t round = 0;

if(pid >= 0){  // fork success

  if(pid > 0){ // father case
    wait(NULL);
    round++;
    printf("PID %d %s\n",getpid(),"ready");
    if (round < 5) {
      exit(0);
      signal(SIGREADY,signal_handle); // ready case
    }
    printf("PID %d %s\n",getpid(),"caught one");
    if ( round >= 5 && round < 10) {
      exit(0);
      signal(SIGCAUGHT,signal_handle); // ready case
    }
    printf("PID %d %s\n",getpid(),"dead");
    if ( round >= 10 && round < 15) {
      exit(0);
      signal(SIGDEAD,signal_handle); // ready case
    }

    }
  else if(pid == 0){ // child case
    wait(NULL);
    if(round <= 4){
     kill(getpid(),SIGREADY);
     signal_handle(SIGREADY);
     exit(0);
   }
   if(round > 4 && round <= 8){
     kill(getpid(),SIGCAUGHT);
     signal_handle(SIGCAUGHT);
     exit(0);
   }
   if(round > 8 && round <= 12){
     kill(getpid(),SIGDEAD);
     signal_handle(SIGDEAD);
     exit(0);
   }
   
}//
}
else{ // failed
  printf("%s\n","fork() failed");
  exit(0);
}
return 0;
}
