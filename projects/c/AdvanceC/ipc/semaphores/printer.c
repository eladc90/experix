#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define KEY 22222


union semun 
{
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
};

int main(int argc, char *argv[])
{
	int sid = -1;
	int status = 0;
	int counter = 1;
	struct sembuf pause = {0, 1, 0};
	struct sembuf resume = {0, -1, 0};
	
	union semun semap;
	semap.val = 1;
	
	if (-1 == (sid = semget(KEY, 1, 0666 | IPC_CREAT)))
	{
		perror("semget error");
		return 0;
	}
	
	if ( -1 == (status = semctl(sid, 0, SETVAL, semap)))
	{
		perror("semop error");
		return 0;
	}
	
	
	while(counter != 70)
	{
		if( -1 == (status = semop(sid, &resume, 1)))
		{
			perror("resume error");
			return 0;
		}
		
		printf("looooooooping for the %dth time\n", counter++);
		
		if( -1 == (status = semop(sid, &pause, 1)))
		{
			perror("pause error");
			return 0;
		}
		
		
	}
	return 0;
} 







	
