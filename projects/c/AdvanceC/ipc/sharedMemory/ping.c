#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/sem.h>
#include <errno.h>
#include <unistd.h>
#define KEY 3333
#define KEY_OF_SEMA 2221
#define SIZE 1300
#define MAX_SIZE 5000


union semun 
{
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
};

typedef struct MS
{
	char m_message[MAX_SIZE];
}MS;

int main()
{
	MS *ms;
	int index = 0;
	int semid;
	int sid = -1;
	int status = 0;
	int counter = 1;
	struct shmid_ds SM; 
	
	struct sembuf pause = {0, 1, 0};
	struct sembuf resume = {0, -1, 0};
	
	union semun semap;
	semap.val = 1;
	
	if (-1 == (sid = shmget(KEY, SIZE, IPC_CREAT | 0660)))
	{
		perror("shmget error");
		return 0;
	}
		
	printf("this is th adress: %p\n", (void *)ms);
	
	if ((ms = (MS *) shmat(sid, NULL, 0)) == (void *) -1)
	{
		perror("shmat error");
		return 0;
	}
	
/*============================ sema ===============================================*/	

	if (-1 == (semid = semget(KEY_OF_SEMA, 1, 0666 | IPC_CREAT)))
	{
		perror("semget error");
		return 0;
	}
	
	if ( -1 == (status = semctl(semid, 0, SETVAL, semap)))
	{
		perror("semop error");
		return 0;
	}
	
	
	printf("this is th adress: %p\n", (void *)ms);
	
	for (; index < 10; index++)
	{
		if( -1 == (status = semop(semid, &resume, 1)))
		{
			perror("resume error");
			return 0;
		}
		
		sprintf(ms -> m_message, "blah a, blah b blah %d\n", index);
		sleep(1);
		 
		if( -1 == (status = semop(semid, &pause, 1)))
		{
			perror("pause error");
			return 0;
		}
		
		printf("this is the message%s\n", ms -> m_message);
	}
	
	
	return 0;
}


/*	if (-1 == (status = shmctl(sid, IPC_RMID, &SM)))*/
/*	{*/
/*		perror("shmctl error");*/
/*		return 0;*/
/*	}*/




