#include stdio.h
#include signal.h
#include stdlib.h
void handler(int sig)父进程自定义信号捕捉函数
{
	pid_t id;
	while((id = waitpid(-1,NULL,WNOHANG))  0){非阻塞式等待
		printf(fatherwait success%dn,id);
	}
	printf(child is quit! %dn,getpid());
}
int main()
{
	signal(SIGCHLD,handler);捕捉SIGCHLD信号
	pid_t id1 = fork();子进程1
	if(id1  0){
		perror(forkn);
		exit(0);
	}
	else if(id1 == 0){child
		printf(child1%dn,getpid());1秒之后退出
		sleep(1);
		exit(1);
	}
	pid_t id2 = fork();子进程2
	if(id2 == 0){
		printf(child2%dn,getpid());
		sleep(2);2秒之后退出
		exit(2);
	}
	pid_t id3 = fork();
	if(id3 == 0){
		printf(child3%dn,getpid());进程3正常运行
	}
	father
	while(1){
		printf(father proc is doing...n);
		sleep(1);
	}
}