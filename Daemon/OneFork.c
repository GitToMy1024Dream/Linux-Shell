#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void mydaemon()
{
	umask(0);//ȱʡֵ��0
	pid_t id = fork();
	if(id > 0){//father
		exit(1);
	}
	setsid();//�����»Ự
	chdir("/");//���Ĺ���Ŀ¼Ϊ��Ŀ¼
	close(0);//�ر�0��1��2�ļ�������
	close(1);
	close(2);
	signal(SIGCHLD,SIG_IGN);//����SIGCHLD�ź�
}
int main()
{
	mydaemon();
	while(1){
		sleep(1);
	}
	return 0;
}