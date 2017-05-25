#include "comm.h"
int main()
{
	int shmid = getShm(0);
	char* buf;
	buf = shmat(shmid,NULL,0);
	int count = 0;
	while(count++ < 15)
	{
		printf("client# %s\n",buf);
		sleep(1);
	}
	shmdt(buf);
	return 0;
}
