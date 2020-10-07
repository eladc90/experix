#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


void SignalHandler(int _signal);

void SignalHandler2(int _signal);


int main(int argc, char *argv[])
{
	int pid = 0;
	int opt, childSig, fatherSig;
	struct sigaction sa, saChild;
	sa.sa_handler = SignalHandler;
	sa.sa_flags = 0;
	
	saChild.sa_handler = SignalHandler2;
	saChild.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigemptyset(&saChild.sa_mask);
	
	while((opt = getopt(argc, argv, "p:c:")) != -1)
	{
		switch(opt)
		{
		case 'p':
			fatherSig = atoi(optarg);
			break;
		case 'c':
			childSig = atoi(optarg);
			break;
		default:
			break;
		}
	}
	if ((pid = fork()) < 0)
	{
		perror("fork error");
	}

	else if (pid == 0)
	{
	 	if (sigaction(fatherSig, &saChild, NULL) == -1)
	 	{
			perror("sigaction");
			exit(1);
		}
		pause();
		printf("this is the son\n");
		sleep(2);
		printf("son send signal\n");
		kill(getppid(), fatherSig);
		printf("son going to sleep\n");
	}
	if (pid > 0)
	{
		
		if (sigaction(childSig, &sa, NULL) == -1)
		{
			perror("sigaction");
			exit(1);
		}
		printf("this is the father\n");
		printf("father send signal\n");
		kill(pid , childSig);
		printf("father going to sleep\n");
		pause();
		printf("father wake up from sleep\n");
	}
}


void SignalHandler(int sig)
{
 	printf("first handler\n");
}

void SignalHandler2(int sig)
{
 	printf("second handler\n");
}





