#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

<<<<<<< HEAD:c/AdvanceC/ipc/pipe/ping.c
#define READ_AND_WRITE 0666
#define MASSAGE_SIZE 100
=======
#define MESSAGE_SIZE 100
static const int s_DEFAULT_PERMISSIONS = S_IREAD | S_IWRITE;
>>>>>>> 5837e480c419d21d6c3423986fe4db7b122486d5:c/AdvanceC/ipc/ping.c


int main(int argc, char *argv[])
{
	int fd;
	int opt;
	int numOfmasseg, workTime, bufferSize, verbose = 0, create = 0, delete = 0;
	int pingIndex;
	char message[MESSAGE_SIZE];
	char fileName[MESSAGE_SIZE];
	
	while((opt = getopt(argc, argv, "vn:p:r:cdvf:")) != -1)
	{
		switch(opt)
		{
			case 'n':
				numOfmasseg = atoi(optarg);
				break;
				
			case 'p':
				workTime = atoi(optarg);
				break;
				
			case 'r':
				bufferSize = atoi(optarg);
				break;
			
			case 'c':
				create = 1;
				break;
			
			case 'd':
				delete = 1;
				break;
				
			case 'v':
				verbose = 1;
				break;
			
			case 'f':
				strcpy(fileName, optarg);
				break;
					
			default:
				printf("error");
				break;
		}	
	}
	
	if (create == 1)
	{
<<<<<<< HEAD:c/AdvanceC/ipc/pipe/ping.c
		mkfifo(fileName, READ_AND_WRITE);
=======
		/* TODO: Check status */
		mkfifo(fileName, s_DEFAULT_PERMISSIONS);
>>>>>>> 5837e480c419d21d6c3423986fe4db7b122486d5:c/AdvanceC/ipc/ping.c
	}
	
	fd = open(fileName, O_WRONLY);
	/* TODO: Check status */
	if (verbose)
	{
		printf("producer starting to write to buffer\n");
	}
	
	for (pingIndex = 0; pingIndex < numOfmasseg; pingIndex++)
	{
		usleep(workTime * 1000);
		
		sprintf(message, "this is the index number: %d\n", pingIndex);
		write(fd, message, bufferSize);
		
		if (verbose)
		{
			printf("producer wrote to buffer\n");
		}
	}
	
	close(fd);
	
	if (delete)
	{
		unlink(fileName);
	}
	
	return 0;	
}


