#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
int main() {
pid_t pid = fork();
if(pid < 0) {
perror("Fork failed");
exit(1);
}
if(pid > 0) {
printf("Parent process started: PID = %d, Child PID = %d\n", getpid(), pid);
printf("Parent terminating to create orphan process...\n");
exit(0);
} else {
printf("Child process started: PID = %d, Parent PID = %d\n", getpid(), getppid());
sleep(2);
printf("Child process after sleep: PID = %d, New Parent PID (init/systemd) = %d\n", getpid(), getppid());
printf("Child process successfully demonstrated orphan state.\n");
}
return 0;
}
