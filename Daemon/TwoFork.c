#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void mydaemon()
{
	umask(0);//ȱʡֵ����
	if(fork() > 0){//��һ��fork
		exit(1);
	}
	setsid();//�����»Ự
	signal(SIGCHLD,SIG_IGN);//����SIGCHLD�ź�
	if(fork() > 0){//�ڶ���fork
		exit(2);
	}
	chdir("/");//���Ĺ���Ŀ¼Ϊ/Ŀ¼
	close(0);
	close(1);
	close(2);
}
int main()
{
	mydaemon();
	while(1){
		sleep(1);
	}
	return 0;
}