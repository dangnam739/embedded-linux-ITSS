#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void sigHandleALRM(int sigNo)
{
    if (sigNo == SIGALRM)
    { //signal handler for SIGALRM

        printf("Signal No (SIGALRM) : %d\n", sigNo);
    }
    if (sigNo == SIGINT)
    { // signal handler for SIGINT
        printf("\nSignal No (SIGINT)  : %d\n", sigNo);
    }
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("No input time.");
        exit(0);
    }

    int pauseSecond = atoi(argv[1]);

    signal(SIGALRM, sigHandleALRM); // Register signal handler for SIGALRM
    signal(SIGINT, sigHandleALRM);  // Register signal handler for SIGINT

    alarm(pauseSecond); // Scheduled alarm after pauseSeconds
    sleep(pauseSecond);
    printf("The program is starting after %d seconds\n", pauseSecond);

    return 0;
}
