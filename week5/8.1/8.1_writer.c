#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
    // ftok to generate unique key
    key_t key = ftok("shmfile", 65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    printf("shared memory id: %d\n", shmid);

    // shmat to attach to shared memory
    char *str = (char *)shmat(shmid, (void *)0, 0);

    printf("Write Data : ");
    gets(str);

    printf("Data written in memory: %s\n", str);

    //detach from shared memory
    shmdt(str);

    return 0;
}
