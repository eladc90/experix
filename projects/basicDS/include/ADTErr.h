#ifndef __ADTERR_H__
#define __ADTERR_H__


typedef enum 
{
	ERR_OK,		
        ERR_GENERAL,
        ERR_NOT_INITIALZED,
        ERR_ALLOCTAION_FAILED,
        ERR_UNDERFLOW,
        ERR_OVERFLOW,
        ERR_WRONG_INDEX,
	ERR_INVALID_INPUT,
	ERR_NULL,
	ERR_QUEUE_FULL,
	ERR_QUEUE_EMPTY,
	ERR_STACK_EMPTY
}ADTErr;

void HandleErr(ADTErr errNum, char *msg);
/* maggic number*/

#endif /* __ADTERR_H__ */
