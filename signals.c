#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<wait.h>
#include<signal.h>
#include<sys/wait.h>



// my signals :: every signal is probably int value
#define SIGREADY 1
#define SIGCAUGHT 2
#define SIGDEAD 3



void signal_handle(int signal){
    if(signal == SIGREADY ) printf("PID %d %s\n",getpid(),"ready");
    else if(signal == SIGCAUGHT ) printf("PID %d %s\n",getpid(),"caught one");
    else if(signal ==  SIGDEAD ) printf("PID %d %s\n",getpid(),"dead");
}

int main(){
// to create 5 process (include the source process), i actually create 4 childs
// for the 4 childrens create , i need to use in 2 times in fork().
// 2^x = childrens , when x is fork() calls.

pid_t pid; // temp value for fork function answer

pid_t zombies[5];

// create 4 process :: TOTAL 5 (father process include that)
for (size_t i = 0; i < 4; i++) {
  pid = fork();
  if(!pid)
    break;
}

for (size_t i = 0; i < 5; i++) {
  if (signal(SIGREADY, signal_handle) == SIG_ERR){
  printf("%s\n","can't catch SIGREADY");
  }
  else{
  sleep(1);
  kill(getpid(),SIGREADY); // kill and catch the signal
  break;
  }
}

for (size_t i = 0; i < 5; i++) {
  if (signal(SIGCAUGHT, signal_handle) == SIG_ERR){
  printf("%s\n","can't catch SIGREADY");
  }
  else{
  sleep(1);
  kill(getpid(),SIGCAUGHT); // kill and catch the signal
  break;
  }
}


pid_t temp; // for the zombies catch

for (size_t i = 0; i < 5; i++) {
  if (signal(SIGDEAD, signal_handle) == SIG_ERR){
  printf("%s\n","can't catch SIGREADY");
  }
  else{
  sleep(1);
  temp = getpid();
  kill(temp,SIGDEAD); // kill and catch the signal
  zombies[i] = temp; // father catch all the zombies
  break;
  }
}

exit(0);
}
