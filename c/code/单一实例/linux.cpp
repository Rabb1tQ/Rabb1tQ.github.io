#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
 
#define PROC_NAME "single_instance"
#define PID_FILE_PATH "/var/run/"
static int lockFile(int fd);
static int isRunning(const char *procname);

int g_fd = -1; 

static int lockFile(int fd)
{
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;
    fl.l_pid = getpid();  //当前进程号，可写可不写，写了后在用F_GETLK时则可以获取到pid
 
    int ret = fcntl(fd, F_SETLK, &fl);
    printf("file lock ret = %d\n", ret);
    return ret;
}
 
static int isRunning(const char *procname)
{
    char buf[16] = {0};
    char fileName[128] = {0};
    snprintf(fileName, sizeof(fileName), "%s%s.pid", PID_FILE_PATH, procname);
 
    //创建文件时如果指定了 O_CREAT，则必须添加权限，否则可能无法读取文件而导致失败
    int g_fd = open(fileName, O_CREAT | O_RDWR, S_IRWXU);
    if(g_fd < 0)
    {
        printf("open file %s failed !\n", fileName);
        return 1;
    }
 
    if(-1 == lockFile(g_fd))
    {
        // printf("%s is alread running !\n", procname);
        struct flock fl;
        fl.l_type = F_WRLCK;
        fl.l_start = 0;
        fl.l_whence = SEEK_SET;
        fl.l_len = 0;
        
        /*这里获取一下已经运行的实例的进程号*/
        if(fcntl(g_fd, F_GETLK, &fl) == 0)
        {
            printf("%s has been run, pid = %d\n", procname, fl.l_pid);
        }
 
        close(g_fd);
        return 1;
    }
    else
    {
        ftruncate(g_fd, 0);
        long pid = getpid();
        snprintf(buf, sizeof(buf), "%ld", pid);
        printf("write pid = %ld to %s!\n", pid, fileName);
 
        write(g_fd, buf, strlen(buf) + 1);
        return 0;
    }
}



int main()
{
    if(isRunning(PROC_NAME))
    {
        exit(-1);
    }
 
    printf("run ok, pid = %d\n", getpid());
    sleep(30);
 
    if(g_fd != -1) 
    {
        close(g_fd);
    }
 
    return 0;
}
