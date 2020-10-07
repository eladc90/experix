#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> 

#define MASSAGE_SIZE 1024




int main(int argc, char *argv[])
{
	int fd[2];
	int pid = 0;
	int opt;
	int numOfmasseg, producerWork, consumerWork, bufferSize, v = 0;
	int parentIndex, childIndex, nOfBytes;
	char massageSize[MASSAGE_SIZE];
	
	if (pipe(fd) == -1)
	{
		printf("piping error");
	}
	
	while((opt = getopt(argc, argv, "vn:p:c:r:")) != -1)
	{
		switch(opt)
		{
			case 'n':
				numOfmasseg = atoi(optarg);
				break;
				
			case 'p':
				producerWork = atoi(optarg);
				break;
				
			case 'c':
				consumerWork = atoi(optarg);
				break;
				
			case 'r':
				bufferSize = atoi(optarg);
				break;
				
			case 'v':
				v = 1;
				break;
					
			default:
				printf("error");
				break;
		}	
	}
	
	pid = fork();
	if (pid < 0)
	{
		printf("fork error");
	}
	else if (pid > 0)
	{
		close(fd[0]);
		
		printf("producer starting to write to buffer\n");
		for (; parentIndex < numOfmasseg; parentIndex++)
		{
			usleep(producerWork * 1000);
			sprintf(massageSize, "this is the index number: %d\n", parentIndex);
			write(fd[1], massageSize, bufferSize);
			printf("producer wrote to buffer\n");
		}
		close(fd[1]);
		wait(NULL);
		
	}
	else if (pid == 0)
	{
		close(fd[1]);
		printf("consumer starting to read from buffer\n");
		while((nOfBytes = read(fd[0], massageSize, bufferSize)) > 0)
		{
			usleep(consumerWork * 1000);
			printf("%s\n", massageSize); 
			printf("consumer read from buffer\n");
			
		}
		close(fd[0]);
		exit(1);
	}
	return 0;	
}

