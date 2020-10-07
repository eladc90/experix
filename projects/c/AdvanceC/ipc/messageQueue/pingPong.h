#ifndef __PINGPONG_H__
#define __PINGPONG_H__

#define PROJECT_ID	2	
#define KEY_PATH "pingPong.h"
#define MAX_SIZE_OF_MESSAGE 1024
#define PING_CHANNEL 2
#define EOF_CHANNEL 4
#define PONG_CHANNEL 6

#define PING_COUNTER_CHANNEL 7
#define PONG_COUNTER_CHANNEL 8

#define DEFAULT_FILE_NAME "pingPong.h"


typedef struct PingArgs PingArgs;

typedef struct PongArgs PongArgs;

typedef struct Message Message;

struct Message
{
	long 	m_type;
	char	m_msg[MAX_SIZE_OF_MESSAGE];
};


struct PingArgs
{
	int m_createFlag;
	int m_deleteFlag;
	int m_verboseFlag;
	int m_eofFlag;
	int m_numOfElement;
	int m_workTime;
	char* m_fileName;
};


struct PongArgs
{
	int m_verboseFlag;
	int m_workTime;
	char* m_fileName;
};







#endif /*__PINGPONG_H__*/
