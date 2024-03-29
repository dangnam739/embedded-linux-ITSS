#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define PIPE_READ 0
#define PIPE_WRITE 1
#define PIPE_READ_WRITE 2
#define STD_IN 0
#define STD_OUT 1
#define BUFFSIZE 80

/**
 * main process
 */
int main(void)
{
    printf("main           : start\n");

    pid_t pid = 0;                 // process ID
    int pipe_c2p[PIPE_READ_WRITE]; // child to parent
    char buf[BUFFSIZE] = {'\0'};
    int readSize = 0;
    memset(pipe_c2p, 0, sizeof(pipe_c2p));

    // create pipe
    if (pipe(pipe_c2p) == -1)
    {
        perror("processGenerate pipe");
        exit(1);
    }

    // create child process
    switch (pid = fork())
    {
    case -1:
        perror("processGenerate fork");
        // close file descriptor for input/output
        close(pipe_c2p[PIPE_READ]);
        close(pipe_c2p[PIPE_WRITE]);
        exit(1);

    case 0:
      printf("childProcess start\n");

      // close file descriptor for input
      close(pipe_c2p[PIPE_READ]);

      strcpy(buf, "write string\n");
      write(pipe_c2p[PIPE_WRITE], buf, strlen(buf) + 1);
      // close file descriptor for output
      close(pipe_c2p[PIPE_WRITE]);
      printf("parentProcess end\n");
      exit(0);

    default:
      printf("parentProcess start\n");

      // close file descriptor for output
      close(pipe_c2p[PIPE_WRITE]);

      while(1){
            if ((readSize = read(pipe_c2p[PIPE_READ], buf, BUFFSIZE)) == 0)
            {
                break;
            }
            write(STD_OUT, buf, readSize);
      }

      // close file descriptor for input
      close(pipe_c2p[PIPE_READ]);
      printf("parentProcess end\n");

      break;
    }
    printf("main           : end\n");
    return 0;
}
