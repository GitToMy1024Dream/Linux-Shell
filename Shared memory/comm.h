#ifndef _COMM_H
#define _COMM_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define PATHNAME "."
#define PROJ_ID 0x6666
int creatShm(int size);
int getShm(int size);
int destroyShm(int shmid);
#endif
