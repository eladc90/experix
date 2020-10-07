#include <stdio.h>
#include <stdlib.h>
#include "../include/DynamicArray.h"
#define MEGIC_NUM 123123123

struct Meeting_t{
    float beginH;
    float endH;
    int roomN;
    int magicNum = MEGIC_NUM;
};

struct Calender_t{
    Meeting_t* AD;
    int meetingCount;
    int roomN;
    int magicNum = MEGIC_NUM;
};

int ParamCheckDynamicArrayDelete(DynamicArray* DynamicArrayPtr, int* Data){
	if (!(DynamicArrayPtr || Data))
	{
		return NULL_ERROR;
	}
	if (DynamicArrayPtr->NumOfElements<=0)
	{
		return UNDERFLOW_ERROR;
	}
	return OK;
}

int ParamCheckDynamicArrayCreate(int size, int blockSize){
	if (size == 0 && blockSize == 0)
	{
		return INVALID_INPUT_ERROR;
	}
	if(size < 0 || blockSize < 0 ){
		return INVALID_INPUT_ERROR;
	}
	return OK;
}

int IncDynamicArray(DynamicArray* DynamicArrayPtr){
	int* tempPtr;
	if (DynamicArrayPtr->dArrayBlockSize==0)
	{
		return OVERFLOW_ERROR;
	}
	tempPtr = (int *) realloc((DynamicArrayPtr->dArray), ((DynamicArrayPtr->dArraySize) + (DynamicArrayPtr->dArrayBlockSize)) *sizeof(int));
	if (tempPtr!=NULL)
	{
		DynamicArrayPtr->dArray = tempPtr;
		DynamicArrayPtr->dArraySize = DynamicArrayPtr->dArraySize+DynamicArrayPtr->dArrayBlockSize;
		return OK;
	}else{
		return REALOC_ERROR;
	}
}

DynamicArray* DynamicArrayCreate(int size, int blockSize){
	DynamicArray* DAPtr;

	if (ParamCheckDynamicArrayCreate(size,blockSize) == OK)
	{
		DAPtr = (DynamicArray*)malloc(sizeof(DynamicArray));
		if (!DAPtr)
		{
			return NULL;
		}
		DAPtr->dArray = (int*)malloc(size * sizeof(int));
		if (!DAPtr->dArray)
		{
			free(DAPtr);
			return NULL;
		}
		DAPtr->dArraySize = size;
		DAPtr->dArrayBlockSize = blockSize;
		DAPtr->NumOfElements = 0;
		DAPtr->magicNum = MEGIC_NUM;
		return DAPtr;
	}
	return NULL;
}

void DynamicArrayDestroy(DynamicArray* DynamicArrayPtr){
	if (DynamicArrayPtr && DynamicArrayPtr->magicNum == MEGIC_NUM)
	{
		DynamicArrayPtr->magicNum = 0;
		if (DynamicArrayPtr->dArray)
		{
			free(DynamicArrayPtr->dArray);
		}
		free(DynamicArrayPtr);
	}
}

int DynamicdArrayInsert(DynamicArray* DynamicArrayPtr,int Data)
{
	int *tempPtr;
	/*check parameters*/
	if (DynamicArrayPtr==NULL)
	{
		return NULL_ERROR;
	}
	/*reallocte array if needed*/
	if (DynamicArrayPtr->NumOfElements==DynamicArrayPtr->dArraySize)
	{
		int status = IncDynamicArray(DynamicArrayPtr);
		if (status!=OK)
		{
			return status;
		}
	}
	/*append int to the end of the list*/
		/* *(*DynamicArrayPtr+*DaNumOfElements) = Data;*/
		DynamicArrayPtr->dArray[DynamicArrayPtr->NumOfElements] = Data;
		DynamicArrayPtr->NumOfElements+=1;

	return OK;
}

int DynamicArrayDelete(DynamicArray* DynamicArrayPtr, int* Data){
	int status;
	status = ParamCheckDynamicArrayDelete(DynamicArrayPtr,Data);
	if (status != OK)
	 {
	 	return status;
	 } 
	DynamicArrayPtr->NumOfElements-=1;
	*Data = DynamicArrayPtr->dArray[DynamicArrayPtr->NumOfElements];
	return OK;
}

