#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHIMSIZE 10
#define KEYFILE_PATH "keyfilepath"
#define PROJ_CHAR 'A'

int main()
{
    int i;
    int shmsize;
    int shmid;
    key_t keyval;
    int *ptr;
    int *head;
    pthread_mutex_t pm;
    pthread_mutexattr_t pmattr;

    // ftok to generate unique key
    keyval = ftok(KEYFILE_PATH, (int)PROJ_CHAR);
    shmsize = SHIMSIZE;

    //allocate mutex to shared memory
    //Get the shared memory ID
    if ((shmid = shmget(keyval, shmsize * sizeof(int),
                        IPC_CREAT | 0660)) == -1)
    {
        perror("shmget");
        exit(1);
    }
    //Attach the shared memory
    ptr = (int *)shmat(shmid, 0, 0);
    head = ptr;

    printf("shared memory id is: %d\n", shmid);

    if ((head == (int *)-1))
    {
        perror("shmat");
        exit(1);
    }

    // Initialize the mutex attribute object
    pthread_mutexattr_init(&pmattr);

    // Set mutex attribute(Setting for using mutex to inter process)
    if (pthread_mutexattr_setpshared(&pmattr, PTHREAD_PROCESS_SHARED) != 0)
    {
        perror("pthread_mutexattr_setpshared");
        exit(1);
    }
    // Initialize mutex
    pthread_mutex_init(&pm, &pmattr);

    // Lock mutex
    if (pthread_mutex_lock(&pm) != 0)
    {
        perror("pthread_mutex_lock");
        exit(1);
    }
    printf("mutex lock\n");

    //Write to the shared memory
    for (i = 0; i != shmsize; i++)
    {
        *ptr++ = i;
    }

    //Detach the shared memory
    if (shmdt((void *)head) == -1)
    {
        perror("shmdt");
        exit(1);
    }

    // Unlock mutex
    if (pthread_mutex_unlock(&pm) != 0)
    {
        perror("pthread_mutex_unlock");
        exit(1);
    }
    printf("mutex unlock\n");

    //Delete the shared memory
    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        perror("shmctl");
        exit(1);
    }

    return 0;
}
