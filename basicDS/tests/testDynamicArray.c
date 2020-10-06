#include <stdio.h>
#include <stdlib.h>
#include "DynamicArray.h"



void testDynamicArrayCreate1(){
    int size = 0,blockSize = 2;
    DynamicArray* DAPtr;
    printf("%s","testDynamicArrayCreate1: ");
    DAPtr = DynamicArrayCreate(size,blockSize);
    if (DAPtr){
        if ((DAPtr->dArray)==NULL)
        {
            printf("%s\n","FAIL");
            return;
        }
        if ((DAPtr->dArraySize)!=0)
        {
            printf("%s\n","FAIL");
            return;
        }
        if ((DAPtr->dArrayBlockSize)!=2)
        {
            printf("%s\n","FAIL");
            return;
        }
        if ((DAPtr->NumOfElements)!=0)
        {
            printf("%s\n","FAIL");
            return;
        }
        printf("%s\n","PASS");
    }else{
        printf("%s\n","FAIL");
    }
    DynamicArrayDestroy(DAPtr);
}
void testDynamicArrayCreate2(){
    int size = 0,blockSize = 0;
    DynamicArray* DAPtr;
    printf("%s","testDynamicArrayCreate2: ");
    DAPtr = DynamicArrayCreate(size,blockSize);
    if (!DAPtr){
        printf("%s\n","PASS");
    }else{
        printf("%s\n","FAIL");     
    }
}
void testDynamicArrayCreate3(){
    int size = -1,blockSize = 0;
    DynamicArray* DAPtr;
    printf("%s","testDynamicArrayCreate3: ");
    DAPtr = DynamicArrayCreate(size,blockSize);
    if (!DAPtr){
        printf("%s\n","PASS");
    }else{
        printf("%s\n","FAIL");     
    }
}

void testDynamicArrayDestroy1(){
    int size = 2,blockSize = 2;
    DynamicArray* DAPtr;
    printf("%s","testDynamicArrayCreate1: ");
    DAPtr = DynamicArrayCreate(size,blockSize);
    DynamicArrayDestroy(DAPtr);
    printf("%s\n","PASS");
}
void testDynamicArrayDestroy2(){
    DynamicArray* DAPtr = NULL;
    printf("%s","testDynamicArrayCreate1: ");
    DynamicArrayDestroy(DAPtr);
    printf("%s\n","PASS");
}

void testDynamicdArrayInsert1(){
    int size = 2,blockSize = 2,status;
    DynamicArray* DAPtr;
    printf("%s","testDynamicdArrayInsert1: ");
    DAPtr = DynamicArrayCreate(size,blockSize);
    status = DynamicdArrayInsert(DAPtr,1);
    if (DAPtr->dArray[0]!=1 || status != OK || DAPtr->dArraySize!=2 || DAPtr->NumOfElements!=1)
    {
        printf("%s\n","FAIL");
        return;
    }
    DynamicArrayDestroy(DAPtr);
    printf("%s\n","PASS");
}
void testDynamicdArrayInsert2(){
    int size = 2,blockSize = 2,status;
    DynamicArray* DAPtr;
    printf("%s","testDynamicdArrayInsert2: ");
    DAPtr = DynamicArrayCreate(size,blockSize);
    status = DynamicdArrayInsert(DAPtr,1);
    status = DynamicdArrayInsert(DAPtr,1);
    status = DynamicdArrayInsert(DAPtr,1);
    status = DynamicdArrayInsert(DAPtr,1);
    status = DynamicdArrayInsert(DAPtr,1);
    status = DynamicdArrayInsert(DAPtr,1);
    status = DynamicdArrayInsert(DAPtr,5);
    if (DAPtr->dArray[6]!=5 || status != OK || DAPtr->dArraySize!=8 || DAPtr->NumOfElements!=7)
    {
        printf("%s\n","FAIL");
        return;
    }
    DynamicArrayDestroy(DAPtr);
    printf("%s\n","PASS");
}
void testDynamicdArrayDelete1(){
    int size = 2,blockSize = 2,status,Data;
    DynamicArray* DAPtr;
    printf("%s","testDynamicdArrayDelete1: ");
    DAPtr = DynamicArrayCreate(size,blockSize);
    status = DynamicdArrayInsert(DAPtr,1);
    status = DynamicdArrayInsert(DAPtr,2);
    status = DynamicdArrayInsert(DAPtr,2);
    status = DynamicArrayDelete(DAPtr,&Data);
    status = DynamicArrayDelete(DAPtr,&Data);
    if (status!=OK || Data != 2)
    {
        printf("%s\n","FAIL");
        return;
    }
    DynamicArrayDestroy(DAPtr);
    printf("%s\n","PASS");
}
void testDynamicdArrayDelete2(){
    int size = 2,blockSize = 2,status,Data;
    DynamicArray* DAPtr;
    printf("%s","testDynamicdArrayDelete2: ");
    DAPtr = DynamicArrayCreate(size,blockSize);
    status = DynamicdArrayInsert(DAPtr,1);
    status = DynamicArrayDelete(DAPtr,&Data);
    status = DynamicArrayDelete(DAPtr,&Data);
    if (status!=UNDERFLOW_ERROR)
    {
        printf("%s\n","FAIL");
        return;
    }
    DynamicArrayDestroy(DAPtr);
    printf("%s\n","PASS");
}


int main()
{
    testDynamicArrayCreate1();
    testDynamicArrayCreate2();
    testDynamicArrayCreate3();
    testDynamicArrayDestroy1();
    testDynamicArrayDestroy2();
    testDynamicdArrayInsert1();
    testDynamicdArrayInsert2();
    testDynamicdArrayDelete1();
    testDynamicdArrayDelete2();
	return 0;
}

