#include <stdio.h>
#include <signal.h>
//打印pending表
void printpending(sigset_t *pending)
{
	int i = 1;
	for(;i < 32;i++)
	{
          //pending信号集中的有效信号如果包含i，返回1，不包含返回0
		if(sigismember(pending,i))
			printf("1 ");
		else
			printf("0 ");
	}
	printf("\n");
        //重新捕捉，从递达到未决
	sigset_t sigset,osigset;
	sigemptyset(&sigset);
	sigemptyset(&osigset);
	sigaddset(&sigset,2);
	sigprocmask(SIG_SETMASK,&sigset,&osigset);
}
void handler(int sig)
{
	printf("sig: %d\n",sig);
	return ;
}
int main()
{
	sigset_t sigset,osigset;//定义两个信号集
	sigemptyset(&sigset);//初始化sigset
	sigemptyset(&osigset);//初始化osigset
	sigaddset(&sigset,2);//将信号集的2号位置1
	sigprocmask(SIG_SETMASK,&sigset,&osigset);//先将sigset的信号屏蔽字备份到osigset中
        //再将sigset设定为当前信号屏蔽字
	signal(2,handler);
	int count = 0;
	sigset_t pending;
	while(1)
	{
		sigpending(&pending);//读取未决信号集
		printpending(&pending);//打印未决表
		sleep(1);
		if(count++ > 5)
		{
              //先将sigset的信号屏蔽字备份到sigset中，再将osigset设定为当前信号屏蔽字
			sigprocmask(SIG_SETMASK,&osigset,&sigset);
			count = 0;//循环起来
		}
	}
}