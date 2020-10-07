#ifndef __ZLOG_H__
#define __ZLOG_H__


#define ZLOG(type , str) (ZlogWrite(type , str ,__FILE__, __LINE__, __func__)


void ZlogWrite(Event _type, char *_str, const char *_fileName, int _lineNumber, char *_func);


void ZlogInit(char *_fileName);




#endif /*__ZLOG_H__*/
