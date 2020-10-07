#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include "../inc/userManager.h"
#include "../inc/userDB.h"
#include "groupMng.h"

#define MAGIC_NUMBER 0xBEEFBEEF
#define DEAD_MAGIC_NUMBER 0xDEADBEEF

UserManager* UserManagerCreate()
{
	UserManager* newUserManager;
	UserDB* newUserDB;

	if(NULL == (newUserDB = UserDBCreate()))
	{
		return NULL;
	}

	if(NULL == (newUserManager = (UserManager *)malloc(sizeof(UserManager))))
	{
		UserDBDestroy(newUserDB);
		return NULL;
	}

	newUserManager->m_db = newUserDB;
	newUserManager->m_magicNumber = MAGIC_NUMBER;

	return newUserManager;
}

void UserManagerDestroy(UserManager* _userManager)
{
	if (NULL != _userManager && MAGIC_NUMBER == _userManager->m_magicNumber)
    {
        _userManager->m_magicNumber = DEAD_MAGIC_NUMBER;
		UserDBDestroy(_userManager->m_db);
        free(_userManager);
    }
}

UserManagerResult UserManagerAdd(UserManager* _userManager, const char* _newUser, const char* _newPassword)
{
	UserDBResult dbResult;
	
	if(NULL == _userManager || MAGIC_NUMBER != _userManager->m_magicNumber || NULL == _newUser || NULL == _newPassword)
	{
		printf("1\n");
		return USERM_UNINITIALIZED_PTRS;
	}

	if(USERDB_ALREADY_EXISTS == (dbResult = UserDBDoesUserExist(_userManager->m_db, _newUser)))
	{
		printf("2\n");
		return USERM_ALREADY_EXISTS;
	}

	if(USERDB_SUCCESS != (dbResult = UserDBAddUser(_userManager->m_db, _newUser, _newPassword)))
	{
		printf("3\n");
		return USERM_FAILURE;
	}
	printf("4\n");
	return USERM_SUCCESS;
}

UserManagerResult UserManagerDelete(UserManager* _userManager, const char* _username)
{
	UserDBResult dbResult;

	if(NULL == _userManager || MAGIC_NUMBER != _userManager->m_magicNumber || NULL == _username)
	{
		return USERM_UNINITIALIZED_PTRS;
	}

	if(USERDB_DOESNT_EXIST == (dbResult = UserDBDoesUserExist(_userManager->m_db, _username)))
	{
		return USERM_DOESNT_EXIST;
	}
	
	if(USERDB_SUCCESS != (dbResult = UserDBDeleteUser(_userManager->m_db, _username)))
	{
		return USERM_FAILURE;
	}

	return USERM_SUCCESS;
}

UserManagerResult UserManagerLogin(UserManager* _userManager, const char* _username, const char* _password)
{
	UserDBResult dbResult;

	if(NULL == _userManager || MAGIC_NUMBER != _userManager->m_magicNumber || NULL == _username || NULL == _password)
	{
		return USERM_UNINITIALIZED_PTRS;
	}

	if(USERDB_DOESNT_EXIST == (dbResult = UserDBIsUserActive(_userManager->m_db, _username)))
	{
		printf("does not exist\n");
		return USERM_DOESNT_EXIST;
	}
	else if(USERDB_ALREADY_CONNECTED == dbResult)
	{
		return USERM_ALREADY_CONNECTED;
	}
	else
	{
		if(USERDB_WRONG_PASSWORD == (dbResult = UserDBCheckUserDetails(_userManager->m_db, _username, _password)))
		{
			return USERM_WRONG_PASSWORD;
		}
	}

	UserDBSetActivity(_userManager->m_db, _username, USER_CONNECTED);
	return USERM_SUCCESS;
}

UserManagerResult UserManagerLogout(UserManager* _userManager, const char* _username)
{
	/* UserDBResult dbResult; */

	if(NULL == _userManager || MAGIC_NUMBER != _userManager->m_magicNumber || NULL == _username)
	{
		return USERM_UNINITIALIZED_PTRS;
	}

	/*
	if(USERDB_DOESNT_EXIST == (dbResult = UserDBIsUserActive(_userManager->m_db, _username)))
	{
		return USERM_DOESNT_EXIST;
	}
	else if(USERDB_DISCONNECTED == dbResult)
	{
		return USERM_DISCONNECTED;
	}
	*/

	UserDBSetActivity(_userManager->m_db, _username, USER_DISCONNECTED);

	/*
	TODO:
		1) decrease counter by 1 in all groups.
		2) if user is the only one in group, delete group.
	*/

	return USERM_SUCCESS;
}


