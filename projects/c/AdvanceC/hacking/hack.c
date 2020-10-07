#include <stdio.h>

long int g = 3;
long int Func1(long int _a, long int _b);

void Func2();


int main()
{
	long int a = 10;
	long int b = 20;
	Func1(a, b);
	printf("returned to main!!!!\n");
	return 0;
}

long int Func1(long int _a, long int _b)
{
	int index = 1;
	long int f1 = 30;
	long int f2 = 40;
	void *ptr = &Func2;
	printf("adress of main : %p \n", &main); 
	printf("adress: %p , val: %ld\n", &f1, f1); 
	printf("adress: %p , val: %ld\n", &f2, f2);
	printf("adress of func is: %p ", &Func1);
	printf("going up: \n");
	for (; index < 10; index++)
	{
		printf("adress: %p , hex val: %-20lx val: %-20ld\n %d", &f1 + index, *(&f1 + index), *(&f1 + index), index);
	}
	printf("going down: \n");
	for (index = 1 ; index < 10; index++)
	{
		printf("adress: %p , hex val: %-20lx val: %-20ld\n ", &f1 -  index, *(&f1 - index),*(&f1 - index));
	}
	printf("\n\n");
	g = *(&f1 + 5);
	*(&f1 + 5) = (long int)Func2;
	/**(&f1 + 6) = (long int)g;*/
	return _a + _b;
}



void Func2()
{
	long int index = -10;
	long int f3 = 80;
	printf("hacked!\n\n");
	return;
}








