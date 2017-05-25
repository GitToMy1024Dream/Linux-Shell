#include "comm.h"
static int commShm(int size,int flags)
{
	key_t _key = ftok(PATHNAME,PROJ_ID);
	if(_key < 0)
	{

		perror("ftok");
		return -1;
	}
	int shmid = shmget(_key,size,flags);
	if(shmid < 0)
	{
		perror("shmid");
		return -2;
	}
	return shmid;
}
int creatShm(int size)
{
	return commShm(size,IPC_CREAT|IPC_EXCL|0666);
}
int getShm(int size)
{
	return commShm(size,IPC_CREAT);
}
int destroyShm(int shmid)
{
	if(shmctl(shmid,IPC_RMID,NULL) < 0)
	{
		perror("destroy");
		return -1;
	}
	return 0;
}
