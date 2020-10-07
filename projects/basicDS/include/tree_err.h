#ifndef __TREE_ERR_H__
#define __TREE_ERR_H__


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
    ERR_INPUT_ALREADY_EXIST,
    ERR_NULL
}ADTErr;

typedef enum
{
    PRE_ORDER, 
    IN_ORDER,
    POST_ORDER
}TreeTraverse;

#endif /*__TREE_ERR_H__ */
