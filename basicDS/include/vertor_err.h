#ifndef __VERTOR_ERR__
#define __VERTOR_ERR__


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
        ERR_REALLOCTAION_FAILED,
        ERR_VECTOR_EMPTY,
	ERR_NULL
}ADTErr;

void HandleErr(ADTErr errNum, char *msg);
/* maggic number*/

#endif /*__VERTOR_ERR__ */
