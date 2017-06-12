#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
void handler(int sig)//�������Զ��岶׽����
{
	pid_t id;
	while(id = waitpid(-1,NULL,0) > 0){//����ʽ�ȴ�
		printf("father:wait success:%d\n",getpid());
	}
	printf("child is quit! %d\n",getpid());
}
int main()
{
	signal(SIGCHLD,handler);//��׽SIGCHLD�ź�
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
	while(1){
		printf("father proc is doing...\n");
		sleep(1);
	}
}