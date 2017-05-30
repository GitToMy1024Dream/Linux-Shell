#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
//互斥锁的初始化
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int count = 0;
void *pthread_run(void *arg)
{
	int val = 0;
	int i =0;
	while(i < 5000)
	{
		//对临界区加锁
		pthread_mutex_lock(&mutex);
		i++;
		val = count;
		printf("pthread:%lu,count:%d\n",pthread_self(),count);
		count = val + 1;
		//解锁操作
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
int main()
{
	pthread_t pth1;
	pthread_t pth2;
	pthread_create(&pth1,NULL,&pthread_run,NULL);
	pthread_create(&pth2,NULL,&pthread_run,NULL);
	pthread_join(pth1,NULL);
	pthread_join(pth2,NULL);
	printf("count: %d\n",count);
	return 0;
}