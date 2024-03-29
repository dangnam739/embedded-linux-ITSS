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

    // Create pipe
    if (pipe(pipe_c2p) == -1)
    {
        perror("processGenerate pipe");
        exit(1);
    }

    // Create child process
    switch (pid = fork())
    {
    case -1:
        perror("processGenerate fork");
        // Close input/output file descriptor of pipe
        close(pipe_c2p[PIPE_READ]);
        close(pipe_c2p[PIPE_WRITE]);
        exit(1);

    case 0:
      printf("childProcess start\n");

      // Switch the file descriptor for the pipe output to a standard input.
      close(STD_OUT);
      dup(pipe_c2p[PIPE_WRITE]);
      // close file descriptor for input/output
      close(pipe_c2p[PIPE_READ]);
      close(pipe_c2p[PIPE_WRITE]);

      execlp("ls", "ls", "-l", NULL);
      // execlp error
      perror("execlp : ls -l");
      exit(1);

    default:
        printf("parentProcess start\n");

        // Switch the file descriptor for the pipe input to a standard input.
        close(STD_IN);
        dup(pipe_c2p[PIPE_READ]);

        // close file descriptor for input/output
        close(pipe_c2p[PIPE_READ]);
        close(pipe_c2p[PIPE_WRITE]);

        execlp("wc", "wc", "-l", NULL);
        // execlp error
        perror("execlp : wc -l");
        exit(1);
    }
    printf("main           : end\n");
    return 0;
}
