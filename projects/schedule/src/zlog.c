#include <time.h>
#include <stdio.h>
#include "../include/zlog.h"
#define NAN_TO_MIL(x)(x / 1000)


static char *g_fileName = "defualt.log"; 

const char *ErrDescript[] = {"trace" , "error", "fatal error"};


void ZlogWrite(Event _type, char *_str, const char *_fileName, int _lineNumber,const char *_func)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	struct timespec timeSpe;
	clockid_t clk_id = CLOCK_MONOTONIC;
	FILE *file;
	file = fopen (g_fileName, "a+");
	if (file == NULL)	
	{
		return;
	}
	clock_gettime(clk_id, &timeSpe);
	fprintf(file, "now: %d-%d-%d %d:%d:%d\nclock:%ld\n", tm.tm_year + 1900, tm.tm_mon + 1,tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, NAN_TO_MIL(timeSpe.tv_nsec));
	
	fprintf(file, "%s %s %s %s%s %s %d %s\n\n\n" ,ErrDescript[_type] ," in file: ", _fileName, " in function: " , _func, " in line: ", _lineNumber, _str);
	fclose(file);
	return;
}



void ZlogInit(char *_fileName)
{
	g_fileName = _fileName;
}






