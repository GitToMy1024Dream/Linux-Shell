#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void mydaemon()
{
	umask(0);//缺省值清零
	if(fork() > 0){//第一次fork
		exit(1);
	}
	setsid();//设置新会话
	signal(SIGCHLD,SIG_IGN);//忽略SIGCHLD信号
	if(fork() > 0){//第二次fork
		exit(2);
	}
	chdir("/");//更改工作目录为/目录
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