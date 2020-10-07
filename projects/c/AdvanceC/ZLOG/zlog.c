#include <time.h>
#include <stdio.h>


#define ZLOG(type , str) (ZlogWrite(type , str ,__FILE__, __LINE__, __func__)




printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1,tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


static char *g_fileName = "defualt.log"; 

typedef enum Event
{
	TRCAE = 0,
	ERROR, 
	FATAL_ERROR, 
}Event;

const char *ErrDescript[] = {"trace" , "error", "fatal error"};

void ZlogWrite(Event _type, char *_str, const char *_fileName, int _lineNumber, char *_func);


void checkZlog();

int main ()
{
    return 0;
}


void ZlogWrite(Event _type, char *_str, const char *_fileName, int _lineNumber, char *_func)
{
	struct tm tm = *localtime(&t);
	time_t t = time(NULL);
	FILE *file;
	file = fopen (g_fileName, "a+");
	if (file == NULL)
	{
		return;
	}
	
	printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1,tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	
	fprintf(file,"%s %s %s %s%s %s %d %s\n" ,ErrDescript[_type] ," in file: ", _fileName, " in function: " , _func, " in line: ", _lineNumber, _str);
	fclose(file);
	return;
}



void ZLogInit(char *_fileName)
{
	g_fileName = _fileName;
}






