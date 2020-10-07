#include <stdio.h> 


struct tes
{
	char ch1;
	int i;
	char ch2;
}tes;



int main()
{
	printf("size of the struct is : %ld\n", sizeof(tes));
	return 0;
}
