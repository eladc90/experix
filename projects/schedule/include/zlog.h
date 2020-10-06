#ifndef __ZLOG_H__
#define __ZLOG_H__


#define ZLOG(type , str) ZlogWrite(type , str ,__FILE__, __LINE__, __func__)


typedef enum 
{
	TRCAE = 0,
	ERROR, 
	FATAL_ERROR
}Event;



void ZlogWrite(Event _type, char *_str, const char *_fileName, int _lineNumber,const char *_func);


void ZlogInit(char *_fileName);




#endif /*__ZLOG_H__*/
