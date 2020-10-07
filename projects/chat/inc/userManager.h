#ifndef __USERMANAGER_H__
#define __USERMANAGER_H__
#include "userDB.h"

/*-------------------------------------- typedefs --------------------------------------*/
typedef enum UserManagerResult
{
	USERM_SUCCESS,			/* Successful operation */
	USERM_FAILURE,			/* Unsuccessful operation */
	USERM_UNINITIALIZED_PTRS,
	USERM_ALREADY_EXISTS,
	USERM_DOESNT_EXIST,
	USERM_WRONG_PASSWORD,
	USERM_ALREADY_CONNECTED,
	USERM_DISCONNECTED,
	USERM_GRP_NOT_EXIST
	/*
	USER_INVALID_USERNAME,
	USER_INVALID_PASSWORD,
	*/
} UserManagerResult;

typedef struct UserManager
{
	size_t m_magicNumber;
	UserDB* m_db;
}UserManager;

/*------------------------------ Main Functions Declaration ------------------------------*/
UserManager* UserManagerCreate();
void UserManagerDestroy(UserManager* _userManager);
UserManagerResult UserManagerAdd(UserManager* _userManager, const char* _newUser, const char* _newPassword);
UserManagerResult UserManagerDelete(UserManager* _userManager, const char* _username);
UserManagerResult UserManagerLogin(UserManager* _userManager, const char* _username, const char* _password);
UserManagerResult UserManagerLogout(UserManager* _userManager, const char* _username);


#endif /* __USERMANAGER_H__ */