#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/fcntl.h>

#define FIFO_FILE_PATH "fifo.txt"
#define BUFF_SIZE 256

int func()
{
    int i;
    int fifoFd;
    char *buf[BUFF_SIZE];
    int size;


    if ((fifoFd = open(FIFO_FILE_PATH, O_WRONLY)) == -1)
    {
        perror("fifofile open");
        exit(1);
    }

    //Output to FIFO file
    while ((size = read(fifoFd, buf, BUFF_SIZE)) != 0)
    {
        printf("%s", buf);
    }

    close(fifoFd);

    return 0;
}

int main()
{
    func();
    return 0;
}
