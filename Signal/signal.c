#include <stdio.h>
#include <signal.h>
//��ӡpending��
void printpending(sigset_t *pending)
{
	int i = 1;
	for(;i < 32;i++)
	{
          //pending�źż��е���Ч�ź��������i������1������������0
		if(sigismember(pending,i))
			printf("1 ");
		else
			printf("0 ");
	}
	printf("\n");
        //���²�׽���ӵݴﵽδ��
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
	sigset_t sigset,osigset;//���������źż�
	sigemptyset(&sigset);//��ʼ��sigset
	sigemptyset(&osigset);//��ʼ��osigset
	sigaddset(&sigset,2);//���źż���2��λ��1
	sigprocmask(SIG_SETMASK,&sigset,&osigset);//�Ƚ�sigset���ź������ֱ��ݵ�osigset��
        //�ٽ�sigset�趨Ϊ��ǰ�ź�������
	signal(2,handler);
	int count = 0;
	sigset_t pending;
	while(1)
	{
		sigpending(&pending);//��ȡδ���źż�
		printpending(&pending);//��ӡδ����
		sleep(1);
		if(count++ > 5)
		{
              //�Ƚ�sigset���ź������ֱ��ݵ�sigset�У��ٽ�osigset�趨Ϊ��ǰ�ź�������
			sigprocmask(SIG_SETMASK,&osigset,&sigset);
			count = 0;//ѭ������
		}
	}
}