#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#define SIZE 64
int ring[SIZE];//���ζ���
sem_t blank_sem;//���ӵ��ź���
sem_t data_sem;//���ݵ��ź���
//������
void* thread_producer(void* arg)
{
    int i = 0;
    while(1)
    {
        sleep(1);
        sem_wait(&blank_sem);//���������Դ�����ӵ��ź�����Դ-1      
		int data = rand()%10000;
        ring[i] = data;
        printf("Producer: %d\n",data);
        i++;
        i %= SIZE;
        sem_post(&data_sem);//�ͷ�������Դ�����ݵ��ź�����Դ+1
    }
}
//������
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