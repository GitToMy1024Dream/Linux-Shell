#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <pwd.h>
#include <string.h>
void GetLogName()
{
    struct passwd* pf;
    pf = getpwuid(getuid());
    printf("[%s@",pf->pw_name);
}
void GetHostName()
{
    char name[128];
    gethostname(name,sizeof(name)-1);
    printf("%s",name);
}
void GetDiretion()
{
    char pwd[128];
    getcwd(pwd,sizeof(pwd)-1);
    int len = strlen(pwd);
    char *p = pwd+len-1;
    while(*p != '/')
    {
        p--;
    }
    p++;
    printf(" %s]# ",p);
}
int main()
{
    while(1)
    {
        GetLogName();//��ȡ�û���
        GetHostName();//��ȡ������
        GetDiretion();//��ȡ��ǰ·��
        fflush(stdout);//ˢ�±�׼���������
        char buf[1024];//��������в���������
        ssize_t s = read(0,buf,sizeof(buf)-1);//�ӱ�׼����0��ȡ����
        if(s > 0)//��ȡ�ɹ�
        {
            buf[s-1] = 0;//ȥ����������ʱ����Ļس�����
        }
        char *_argv[32];//ָ�����������������
        _argv[0] = buf;
        int i = 1;
        char *start = buf;
        while(*start)
        {
            if(*start == ' ')
            {
                *start = 0;
                start++;
                _argv[i++] = start;
            }
            else
                start++;
        }
        _argv[i] = NULL;
        //��������ض������
        if(strcmp(_argv[i-2],">") ==0)
        {
            _argv[i - 2] = NULL;
            pid_t id = fork();
            if(id < 0)//��������ʧ��
                perror("fork");
            else if(id == 0)//child
            {
                close(1);
                open(_argv[i-1],O_WRONLY | O_CREAT,0664);
                execvp(_argv[0],_argv);
            }
            else//father
                wait(0);//�ȴ��ӽ���ִ����  
        }
        else
        {
            pid_t id = vfork();
            if(id < 0)//���̴���ʧ��
            {
                perror("vfork");
            }
            else if(id == 0)//child
            {
                execvp(_argv[0],_argv);//��������
            }
            else//father
                wait(0);//�ȴ��ӽ���ִ����  
        }
    }
    return 0;
}