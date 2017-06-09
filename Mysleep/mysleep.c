#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void handler(int sig)
{
   //句柄函数
}
int mysleep(int seconds)
{
	struct sigaction act,oldact;
	act.sa_handler = handler;//设置自定义捕捉函数
	sigemptyset(&act.sa_mask);//初始化信号集
	act.sa_flags = 0;//默认一般为0
	sigaction(SIGALRM,&act,&oldact);//注册信号处理函数
	alarm(seconds);//设置闹钟
	pause();//挂起等待，直到有信号递达
	int time = alarm(0);//取消闹铃
	sigaction(SIGALRM,&oldact,NULL);//恢复默认信号处理动作
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
