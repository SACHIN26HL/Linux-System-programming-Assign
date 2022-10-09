#include<stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
   int pid;
   system("ps -f");
   pid = fork();
   if (pid == 0) {
      printf("Child: pid is %d and ppid is %d\n",getpid(),getppid());
      sleep(5);
      printf("Child: pid is %d and ppid is %d\n",getpid(),getppid());
      system("ps -f");
   } else {
      printf("Parent: pid is %d and ppid is %d\n",getpid(),getppid());
      sleep(2);
      exit(0);
   }
   return 0;
}
