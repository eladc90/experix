#define _GNU_SOURCE
#include <stdio.h> /* printf */
#include <unistd.h>  /* getopt */
#include <stdlib.h> /* atoi */
#include <sys/types.h> /* ftok */
#include <sys/ipc.h> 
#include <sys/msg.h> /* message Queue */  
#include <string.h> 
#include <sys/stat.h>
#include <errno.h>
#include "pingPong.h"

#define PRINT_IF_V(V,...) do { if (V) printf(__VA_ARGS__); } while(0)

#define MAX_SIZE_OF_MESSAGE 1024

static const int sg_DEFAULT_PERMISSIONS = (S_IREAD | S_IWRITE);
const char SEND_MSG[]	= "Message #%2d";
const char END_MSG[] = "end of file";
const char ECHO_ARGS[]	= "Ping: send %d messages every %d msec\n";
const char COUNT_MSG[] = "ping entered";		





/*=================================== statics functions ====================================*/

static void InitArgs(PingArgs *_PingArgs, int _argc, char *_argv[]);

/*==========================================================================================*/



int main(int argc, char *argv[])
{
	Message sendMSG;
	Message reciveMSG;
	int nBytes = 0;
	int status = 0;
	int index = 0;
	int qid = 0;
	key_t key = 0;
	PingArgs Args = {0};
	Args.m_fileName = DEFAULT_FILE_NAME;
	InitArgs(&Args, argc, argv);
	
	PRINT_IF_V(Args.m_verboseFlag, ECHO_ARGS ,Args.m_numOfElement, Args.m_numOfElement);

	if ((key = ftok(Args.m_fileName, PROJECT_ID)) == -1)
	{
		printf("error: key create fail\n");
		return -1;
	}
	printf("%d\n", Args.m_createFlag);
	if (Args.m_createFlag)
	{
		if ((qid = msgget(key, IPC_CREAT | IPC_EXCL | sg_DEFAULT_PERMISSIONS)) == -1)
		{
			
			printf("error: can't create a message queue\n");
			return -1;
		}
		if (Args.m_verboseFlag)
		{	
			printf("ping create a message queue\n");
		}
	}
	else
	{
		if((qid = msgget(key, sg_DEFAULT_PERMISSIONS)) == -1)
		{
			perror("error");
			return -1;
		}
	}
	
	sprintf(sendMSG.m_msg , COUNT_MSG);
	sendMSG.m_type = PING_COUNTER_CHANNEL;
	if ((status = msgsnd(qid, &sendMSG, strlen(sendMSG.m_msg), IPC_NOWAIT)) == -1)
	{
		printf("sendin message failed\n");
	}
	
	
	for(; index < Args.m_numOfElement; index++)
	{
		sprintf(sendMSG.m_msg , SEND_MSG, index);
		sendMSG.m_type = PING_CHANNEL;
		if ((status = msgsnd(qid, &sendMSG, strlen(sendMSG.m_msg), IPC_NOWAIT)) == -1)
		{
			printf("sendin message failed\n");
		}
		if ((nBytes = msgrcv(qid, &reciveMSG, MAX_SIZE_OF_MESSAGE, PONG_CHANNEL , 0)) == -1)
		{
			printf("receive message failed\n");
		}
		printf("%s\n",  reciveMSG.m_msg);
		usleep(Args.m_workTime);
	}
	
	if ((-1 == (nBytes = msgrcv(qid, &reciveMSG, MAX_SIZE_OF_MESSAGE, PONG_COUNTER_CHANNEL , MSG_COPY | IPC_NOWAIT)))  && (errno == ENOMSG))
	{
		
		if (Args.m_eofFlag)
		{
			sprintf(sendMSG.m_msg , END_MSG);
			sendMSG.m_type = EOF_CHANNEL;
			if ((status = msgsnd(qid, &sendMSG, strlen(sendMSG.m_msg), IPC_NOWAIT)) == -1)
			{
				printf("sendin message failed\n");
			}
		}
		else 
		{
			sprintf(sendMSG.m_msg , END_MSG);
			if ((status = msgsnd(qid, &sendMSG, strlen(sendMSG.m_msg), IPC_NOWAIT)) == -1)
			{
				printf("sendin message failed\n");
			}
		}
		
		if ((nBytes = msgrcv(qid, &reciveMSG, MAX_SIZE_OF_MESSAGE, PING_COUNTER_CHANNEL , 0)) == -1)
		{
			printf("receive message failed\n");
		}
	}
	else
	{
		printf("no more");
	}
	return 0;
}





static void InitArgs(PingArgs *_PingArgs, int _argc, char *_argv[])
{
	int opt = 0;
	
	while ((opt = getopt(_argc, _argv, "cdvf:en:w:")) != -1)
	{
		switch(opt)
		{
			case 'c':
				_PingArgs -> m_createFlag = 1;
				break;
			
			case 'd':
				_PingArgs -> m_deleteFlag = 1;
				break;
			
			case 'v':
				_PingArgs -> m_verboseFlag = 1;
				break;
				
			case 'f':
				_PingArgs -> m_fileName = optarg;
				break;
				
			case 'e':
				_PingArgs -> m_eofFlag = 1;
				break;
				
			case 'n':
				_PingArgs -> m_numOfElement = atoi(optarg);
				break;
				
			case 'w':
				_PingArgs -> m_workTime = atoi(optarg) * 1000; /* TODO */
				break;
				
			default:
				printf("error: flag do not exist");
				break;
		}
	}
}


