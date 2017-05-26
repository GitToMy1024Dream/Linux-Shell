#include "comm.h"
int main()
{
	int shmid = creatShm(4095);
	char *buf;
	buf = shmat(shmid,NULL,0);
	sleep(5);
	int count = 0;
	while(count < 26)
	{
		buf[count++] = 'a' + count;
		buf[count] = '\0';
		sleep(1);
	}
	shmdt(buf);
	destroyShm(shmid);
	return 0;
}
