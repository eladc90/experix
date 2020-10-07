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
	struct sigaction saFather, saChild;
	saFather.sa_handler = SignalHandler;
	saFather.sa_flags = 0;
	
	saChild.sa_handler = SignalHandler2;
	saChild.sa_flags = 0;
	sigemptyset(&saFather.sa_mask);
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
	
	 if (sigaction(fatherSig, &saFather, NULL) == -1)
	 {
		 perror("sigaction");
		 exit(1);
	 }
	  if (sigaction(childSig, &saChild, NULL) == -1)
	 {
		 perror("sigaction");
		 exit(1);
	 }
	 
	 
	
	if ((pid = fork()) < 0)
	{
		perror("fork error");
	}
	
	if (pid > 0)
	{
		printf("father send signal\n");
		kill(pid , fatherSig);
		printf("father going to sleep\n");
		pause();
		printf("father wake up from sleep\n");
	}
	else if (pid == 0)
	{
		pause();
		printf("son send signal\n");
		kill(getppid(), childSig);
		printf("son going to sleep\n");
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
