#include "../include/zlog.h"
#include <stdio.h>



int main()
{
	ZlogInit("STS.log");
	ZLOG(ERROR, "i am in test"));
}

