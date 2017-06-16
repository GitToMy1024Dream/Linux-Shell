#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void mydaemon()
{
	umask(0);//缺省值清0
	pid_t id = fork();
	if(id > 0){//father
		exit(1);
	}
	setsid();//设置新会话
	chdir("/");//更改工作目录为根目录
	close(0);//关闭0、1、2文件描述符
	close(1);
	close(2);
	signal(SIGCHLD,SIG_IGN);//忽略SIGCHLD信号
}
int main()
{
	mydaemon();
	while(1){
		sleep(1);
	}
	return 0;
}