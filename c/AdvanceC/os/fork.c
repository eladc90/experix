#include <stdio.h>
#include <unistd.h>



int g_var = 0;

int main ()
{
	int index = 0;
	int n;
	int lVar = 0;
	n = fork();
	if (n > 0)
	{
		for (; index < 30; index++)
		{
			printf("pa:  ");
			++g_var;
			++lVar;
			printf("g_var is: %d\n", g_var);
			printf("lVar is: %d\n", lVar);
			sleep(1);
		}	
	}
	else
	{
		for (; index < 30; index++)
		{
			printf("son:  ");
			--g_var;
			--lVar;
			printf("g_var is: %d\n", g_var);
			printf("lVar is: %d\n", lVar);
			sleep(1);
		}	
	}
	return 0;
}
