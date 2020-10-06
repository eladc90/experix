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
const char SEND_MSG[]	= "Message #%2d received";
const char COUNT_PONGS[] = "pong added";
const char ECHO_ARGS[]	= "Ping: send %d messages every %d msec\n";
const char END_MSG[] = "end of file";
				




/*=================================== statics functions ====================================*/

static void InitArgs(PongArgs *_PingArgs, int _argc, char *_argv[]);

/*==========================================================================================*/


int main(int argc, char *argv[])
{
	Message reciveMSG;
	Message sendMSG;
	int status = 0;
	int nBytes = 0;
	int qid = 0;
	int index = 1;
	key_t key = 0;
	PongArgs args = {0};
	args.m_fileName = DEFAULT_FILE_NAME;
	InitArgs(&args, argc, argv);
	
	
	
	if (-1 == (key = ftok(args.m_fileName, PROJECT_ID)))
	{
		perror("error is");
		return errno;
	}

	if(-1 == (qid = msgget(key, 0)))
	{
			perror("error is");
			return -1;
	}
	
	sprintf(sendMSG.m_msg , COUNT_PONGS);
	sendMSG.m_type = PONG_COUNTER_CHANNEL;
	if ((status = msgsnd(qid, &sendMSG, strlen(sendMSG.m_msg), IPC_NOWAIT)) == -1)
	{
		printf("sendin message failed\n");
	}
	
	while(1)
	{
		usleep(args.m_workTime);
		if (-1 == (nBytes = msgrcv(qid, &reciveMSG, MAX_SIZE_OF_MESSAGE, -EOF_CHANNEL , 0)))
		{
			printf("receive message failed\n");
		}
		
		if (reciveMSG.m_type != EOF_CHANNEL)
		{
			printf("%s\n",  reciveMSG.m_msg);
			sprintf(sendMSG.m_msg , SEND_MSG, index);
			sendMSG.m_type = PONG_CHANNEL;
			index++;
			if ((status = msgsnd(qid, &sendMSG, strlen(sendMSG.m_msg), IPC_NOWAIT)) == -1)
			{
				printf("sendin message failed\n");
			}
		}

		else if (reciveMSG.m_type == EOF_CHANNEL)
		{
			if ((nBytes = msgrcv(qid, &reciveMSG, MAX_SIZE_OF_MESSAGE, PONG_COUNTER_CHANNEL , MSG_COPY | IPC_NOWAIT)) == -1 && errno == ENOMSG)
			{
				printf("end of file!!\n");
			}
			else
			{
				sprintf(sendMSG.m_msg , END_MSG);
				sendMSG.m_type = EOF_CHANNEL;
				
				if ((status = msgsnd(qid, &sendMSG, strlen(sendMSG.m_msg), IPC_NOWAIT)) == -1)
				{
					printf("sendin EOF message failed\n");
				}
			}
			break;
		}
	} 
	return 0;
}



static void InitArgs(PongArgs *_PongArgs, int _argc, char *_argv[])
{
	int opt = 0;
	
	while ((opt = getopt(_argc, _argv, "vf:w:")) != -1)
	{
		switch(opt)
		{
			case 'v':
				_PongArgs -> m_verboseFlag = 1;
				break;
				
			case 'f':
				_PongArgs -> m_fileName = optarg;
				break;
				
			case 'w':
				_PongArgs -> m_workTime = atoi(optarg) * 1000; /* TODO */
				break;
				
			default:
				printf("error: flag do not exist");
				break;
		}
	}
}
