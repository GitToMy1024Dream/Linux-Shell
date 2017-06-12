#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
void handler(int sig)//父进程的自定义捕捉函数
{
	printf("child is quit! %d\n",getpid());
}
int main()
{
	signal(SIGCHLD,handler);//捕捉SIGCHLD信号
	pid_t id = fork();
	if(id < 0){
		perror("fork\n");
		exit(0);
	}
	else if(id == 0){//child
		printf("child:%d\n",getpid());
		sleep(3);
		exit(1);
	}
	//father
	while(1);
	return 0;
}