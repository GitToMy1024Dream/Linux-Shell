#include stdio.h
#include signal.h
#include stdlib.h
void handler(int sig)�������Զ����źŲ�׽����
{
	pid_t id;
	while((id = waitpid(-1,NULL,WNOHANG))  0){������ʽ�ȴ�
		printf(fatherwait success%dn,id);
	}
	printf(child is quit! %dn,getpid());
}
int main()
{
	signal(SIGCHLD,handler);��׽SIGCHLD�ź�
	pid_t id1 = fork();�ӽ���1
	if(id1  0){
		perror(forkn);
		exit(0);
	}
	else if(id1 == 0){child
		printf(child1%dn,getpid());1��֮���˳�
		sleep(1);
		exit(1);
	}
	pid_t id2 = fork();�ӽ���2
	if(id2 == 0){
		printf(child2%dn,getpid());
		sleep(2);2��֮���˳�
		exit(2);
	}
	pid_t id3 = fork();
	if(id3 == 0){
		printf(child3%dn,getpid());����3��������
	}
	father
	while(1){
		printf(father proc is doing...n);
		sleep(1);
	}
}