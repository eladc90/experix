#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define KEY 22222

int main(int argc, char *argv[])
{
	int status = 0;
	int sid = -1;
	int opt = 0;
	struct sembuf pause = {0, 1, 0};
	struct sembuf resume = {0, -1, 0};
	
	if (-1 == (sid = semget(KEY, 1, 0666 )))
	{
		perror("semget error");
		return 0;
	}
	
	printf("the sid: %d\n", sid);
	while ((opt = getopt(argc, argv, "pr")) != -1)
	{
		switch(opt)
		{
			case 'p':
				if( 0 == (status = semop(sid, &resume, 1)))
				{
					perror("pause error");
					return 0;
				}
				break;
				
			case 'r':
				if( 0 == (status = semop(sid, &pause, 1)))
				{
					perror("pause error");
					return 0;
				}
				break;
			
			
		}
	}	
}
