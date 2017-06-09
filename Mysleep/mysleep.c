#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void handler(int sig)
{
   //�������
}
int mysleep(int seconds)
{
	struct sigaction act,oldact;
	act.sa_handler = handler;//�����Զ��岶׽����
	sigemptyset(&act.sa_mask);//��ʼ���źż�
	act.sa_flags = 0;//Ĭ��һ��Ϊ0
	sigaction(SIGALRM,&act,&oldact);//ע���źŴ�����
	alarm(seconds);//��������
	pause();//����ȴ���ֱ�����źŵݴ�
	int time = alarm(0);//ȡ������
	sigaction(SIGALRM,&oldact,NULL);//�ָ�Ĭ���źŴ�����
	return time;
}
int main()
{
	while(1)
	{
		mysleep(2);
		printf("sleeping...\n");
	}
	return 0;
}
