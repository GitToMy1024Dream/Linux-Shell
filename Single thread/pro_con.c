#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cond = PTHREAD_MUTEX_INITIALIZER;
typedef struct list
{
	int _data;
	struct list* _next;
}Node,*pNode;
typedef struct linklist
{
	Node *phead;
}linklist,*plinklist;
pNode CreatNode(int data)
{
	pNode newNode = (pNode)malloc(sizeof(Node));
	if(NULL == newNode)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	newNode->_data = data;
	newNode->_next = NULL;
	return newNode;
}
void InitList(plinklist plist)
{
	assert(plist);
	plist->phead = NULL;
}
void Push(plinklist list,int data)
{
	assert(list);
	pNode newNode = CreatNode(data);
	if(list->phead == NULL)
	{
		list->phead = newNode;
		return;
	}
	newNode->_next = list->phead;
	list->phead = newNode;
}
void Pop(plinklist list,int* data)
{
	assert(list);
	if(list->phead == NULL)
	{
		printf("list is empty!\n");
		return ;
	}
	pNode pDel = list->phead;
	*data = pDel->_data;
	list->phead = pDel->_next;
	pDel->_next = NULL;
	free(pDel);
	pDel = NULL;
}
void Destroy(plinklist list)
{
	assert(list);
	if(list->phead != NULL)
	{
		pNode pCur = list->phead;
		while(pCur)
		{
			pNode pDel = pCur;
			pCur = pCur->_next;
			free(pDel);
			pDel = NULL;
		}
	}
	list->phead = NULL;
}
void *producter(void *arg)
{
	plinklist list = (plinklist)arg;
	while(1)
	{
		sleep(1);
		pthread_mutex_lock(&lock);//����
		Push(list,rand()%1000);//ͷ�����ֵ
		pthread_cond_signal(&cond);//���ѵȴ��ڸ������������߳�
		pthread_mutex_unlock(&lock);//����
		printf("producter: %d\n",list->phead->_data);
	}
}
void consumer(void *arg)
{
	plinklist list = (plinklist)arg;
	while(1)
	{
		sleep(1);
		pthread_mutex_lock(&lock);//����
		int data = 0;
		while(list->phead == NULL)
		{
			pthread_cond_wait(&cond,&lock);//����Ϊ�գ�consumer�ȴ�
		}
		Pop(list,&data);
		pthread_mutex_unlock(&lock);//����
		printf("consumer: %d\n",data);
	}
}
int main()
{
	linklist list;
	InitList(&list);
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,producter,(void*)&list);//�����߳�
	pthread_create(&tid2,NULL,consumer,(void*)&list);
	pthread_join(tid1,NULL);//�ȴ��߳̽�������
	pthread_join(tid2,NULL);
	Destroy(&list);
	return 0;
}