
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main()
{
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1){
        printf("creat pipe error!\n");
        return 1;
    }
    pid_t id = fork();
    if(id < 0){
        printf("fork child error!\n");
        return 2;
    }
    else if(id == 0)//child
    {
        close(fd[0]);//close read
        int i = 0;
        char* str = NULL;
        while(i < 100)
        {
            str = "i am child";
            write(fd[1],str,strlen(str)+1);
            sleep(1);
            i++;
        }
    }
    else //father
    {
        close(fd[1]);//close write
        char msg[100];
        int j = 0;
        while(j < 100)
        {
            memset(msg,'\0',sizeof(msg));
            read(fd[0],msg,sizeof(msg));
            printf("%s \n",msg);
            ++j;
        }
    }
    return 0;
}