#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#define SIZE 64
int ring[SIZE];//环形队列
sem_t blank_sem;//格子的信号量
sem_t data_sem;//数据的信号量
//生产者
void* thread_producer(void* arg)
{
    int i = 0;
    while(1)
    {
        sleep(1);
        sem_wait(&blank_sem);//申请格子资源，格子的信号量资源-1      
		int data = rand()%10000;
        ring[i] = data;
        printf("Producer: %d\n",data);
        i++;
        i %= SIZE;
        sem_post(&data_sem);//释放数据资源，数据的信号量资源+1
    }
}
//消费者
void* thread_consumer(void* arg)
{
    int i = 0;
    while(1)
    {
        sleep(1);
        sem_wait(&data_sem); //P(data)
        printf("Consumer: %d\n",ring[i]);
        i++;
        i %= SIZE; 
        sem_post(&blank_sem);//V(blank)
    }
}
int main()
{
    sem_init(&blank_sem,0,SIZE);
    sem_init(&data_sem,0,0);
    pthread_t producer;
    pthread_t consumer;
    pthread_create(&producer,NULL,thread_producer,NULL);
    pthread_create(&consumer,NULL,thread_consumer,NULL);
    pthread_join(producer,NULL);
    pthread_join(consumer,NULL);
    sem_destroy(&blank_sem);
    sem_destroy(&data_sem);
    return 0;
}