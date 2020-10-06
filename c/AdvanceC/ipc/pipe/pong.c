#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MESSAGE_SIZE 100
#define DEFAULT_MKFIFO_NAME "h61.elad"
#define DEFAULT_READ_SIZE 32

int main(int argc, char *argv[])
{
	int fd;
	int opt;
	int workTime;
	int bufferSize = DEFAULT_READ_SIZE;
	int verbose = 0;
	char message[MESSAGE_SIZE];
/*	char fileName[MESSAGE_SIZE];
 */ char* fileName = DEFAULT_MKFIFO_NAME;
	int nOfBytes;
	
	while((opt = getopt(argc, argv, "vp:r:f:")) != -1)
	{
		switch(opt)
		{
			case 'p':
				workTime = atoi(optarg);
				break;
				
			case 'r':
				/* TODO: verify that enough space is allocated */
				bufferSize = atoi(optarg);
				break;
				
			case 'v':
				verbose = 1;
				break;
			
			case 'f':
				fileName = optarg;
/*				strcpy(fileName, optarg);
 */				break;
					
			default:
				printf("error");
				break;
		}
	}

	/* TODO: check success */
	fd = open(fileName, O_RDONLY);
	
	if (verbose) {
		printf("consumer starting to read from buffer\n");
	}
	
	while(0 > (nOfBytes = read(fd, message, bufferSize)))
	{
		if (verbose) {
			printf("consumer read :'%s'\n", message); 
		}
		/* simulate work cycle */
		/* TODO: adjust workTime before the loop */
		usleep(workTime * 1000);
	}
	return 0;	
}






