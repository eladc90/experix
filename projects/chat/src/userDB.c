#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <string.h> /* strcmp, strcpy*/
#include "../inc/userDB.h"
#include "../inc/hashmap.h"
#include "../inc/list.h"
#include "../inc/list_itr.h"
#include "../inc/list_functions.h"

#define MAGIC_NUMBER 0xBEEFBEEF
#define DEAD_MAGIC_NUMBER 0xDEADBEEF
#define CONTAINER_CAPACITY 10
#define MAX_LEN_USERNAME 16
#define MAX_LEN_PASSWORD 16
#define FALSE 0
#define TRUE 1

/*-------------------------------------- typedefs --------------------------------------*/
struct User
{
	char m_username[MAX_LEN_USERNAME];
	char m_password[MAX_LEN_PASSWORD];
	ActivityStatus m_activeStatus;
	/* List *m_groupsList; */
};

struct UserDB
{
	size_t m_magicNumber;
	HashMap *m_usersContainer;
};

/*------------------------------ Help Functions Declaration ------------------------------*/
static size_t HashFunc(const void *_key);
static int EqualFunc(const void *_firstKey, const void *_secondKey);
static User *CreateUserStruct(const char *_newUser, const char *_newPassword);

/*------------------------------ Main Functions Implementation ------------------------------*/

UserDB *UserDBCreate()
{
	UserDB *newUserDB;
	HashMap *newHash;

	if (NULL == (newHash = HashMapCreate(CONTAINER_CAPACITY, HashFunc, EqualFunc)))
	{
		return NULL;
	}

	if (NULL == (newUserDB = (UserDB *)malloc(sizeof(UserDB))))
	{
		HashMapDestroy(&newHash, NULL, NULL);
		return NULL;
	}

	newUserDB->m_usersContainer = newHash;
	newUserDB->m_magicNumber = MAGIC_NUMBER;

	return newUserDB;
}

void UserDBDestroy(UserDB *_userDB)
{
	if (NULL != _userDB && MAGIC_NUMBER == _userDB->m_magicNumber)
	{
		_userDB->m_magicNumber = DEAD_MAGIC_NUMBER;
		HashMapDestroy(&_userDB->m_usersContainer, NULL, NULL);
		free(_userDB);
	}
}

UserDBResult UserDBAddUser(UserDB *_userDB, const char *_newUser, const char *_newPassword)
{
	MapResult addResult;
	User *newUserStruct;

	if (NULL == _userDB || MAGIC_NUMBER != _userDB->m_magicNumber || NULL == _newUser || NULL == _newPassword)
	{
		return USERDB_UNINITIALIZED_PTRS;
	}

	if (NULL == (newUserStruct = CreateUserStruct(_newUser, _newPassword)))
	{
		return USERDB_FAILURE;
	}
	printf("this pass before insert to hash %s\n", _newPassword);
	if (MAP_SUCCESS != HashMapInsert(_userDB->m_usersContainer, _newUser, newUserStruct))
	{
			return USERDB_FAILURE;
	}

	return USERDB_SUCCESS;
}

UserDBResult UserDBDeleteUser(UserDB *_userDB, const char *_username)
{
	MapResult deleteResult;
	char *pKey;
	User *pValue;

	if (NULL == _userDB || MAGIC_NUMBER != _userDB->m_magicNumber || NULL == _username)
	{
		return USERDB_UNINITIALIZED_PTRS;
	}

	if (MAP_SUCCESS != (deleteResult = HashMapRemove(_userDB->m_usersContainer, _username, (void **)&pKey, (void **)&pValue)))
	{
		return USERDB_FAILURE;
	}

	return USERDB_SUCCESS;
}

UserDBResult UserDBDoesUserExist(UserDB *_userDB, const char *_username)
{
	MapResult findResult;
	User *pValue;

	if (NULL == _userDB || MAGIC_NUMBER != _userDB->m_magicNumber || NULL == _username)
	{
		return USERDB_UNINITIALIZED_PTRS;
	}

	if (MAP_KEY_NOT_FOUND_ERROR == HashMapFind(_userDB->m_usersContainer, _username, (void **)&pValue))
	{
		printf("HERE\n");
		return USERDB_DOESNT_EXIST;
	}
	return USERDB_ALREADY_EXISTS;
}

UserDBResult UserDBCheckUserDetails(UserDB *_userDB, const char *_username, const char *_password)
{
	MapResult findResult;
	User *pValue;

	if (NULL == _userDB || MAGIC_NUMBER != _userDB->m_magicNumber || NULL == _username || NULL == _password)
	{
		return USERDB_UNINITIALIZED_PTRS;
	}

	if (MAP_SUCCESS != (findResult = HashMapFind(_userDB->m_usersContainer, _username, (void **)&pValue)))
	{
		return USERDB_DOESNT_EXIST;
	}
	printf("this is the pass = %s\n", _password);
	printf("this is the cmp pass = %s\n", pValue->m_password);

	if (!strcmp(pValue->m_password, _password))
	{
		return USERDB_RIGHT_PASSWORD;
	}

	return USERDB_WRONG_PASSWORD;
}

UserDBResult UserDBIsUserActive(UserDB *_userDB, const char *_username)
{
	MapResult findResult;
	User *pValue;

	if (NULL == _userDB || MAGIC_NUMBER != _userDB->m_magicNumber || NULL == _username)
	{
		return USERDB_UNINITIALIZED_PTRS;
	}

	if (MAP_SUCCESS != (findResult = HashMapFind(_userDB->m_usersContainer, _username, (void **)&pValue)))
	{
		return USERDB_DOESNT_EXIST;
	}

	if (pValue->m_activeStatus == USER_DISCONNECTED)
	{
		return USERDB_DISCONNECTED;
	}

	return USERDB_ALREADY_CONNECTED;
}

void UserDBSetActivity(UserDB *_userDB, const char *_username, ActivityStatus _newActivity)
{
	MapResult findResult;
	User *pValue;

	if (NULL != _userDB && MAGIC_NUMBER == _userDB->m_magicNumber && NULL != _username)
	{
		if (MAP_SUCCESS == (findResult = HashMapFind(_userDB->m_usersContainer, _username, (void **)&pValue)))
		{
			pValue->m_activeStatus = _newActivity;
		}
	}
}

/*
ActivityStatus UserDBGetActivity(UserDB* _userDB, const char* _username)
{
	MapResult findResult;
	User* pValue;

	if(MAP_SUCCESS != (findResult = HashMapFind(_userDB->m_usersContainer, _username, &pValue)))
	{
		return USERDB_DOESNT_EXIST;
	}

	return pValue->m_activeStatus;
}
*/

/*------------------------------ Help Functions Implementation ------------------------------*/
static size_t HashFunc(const void *_key)
{
	char username[MAX_LEN_USERNAME];
	int i, asciiSum = 0;

	strcpy(username, (char *)_key);
	for (i = 0; i < strlen(username); i++)
	{
		asciiSum += (((char *)username)[i] + '0');
	}
	return asciiSum;
}

static int EqualFunc(const void *_firstKey, const void *_secondKey)
{

	return strcmp((const char *)_firstKey, (const char *)_secondKey) == 0;
}

static User *CreateUserStruct(const char *_newUser, const char *_newPassword)
{
	User *newUserStruct;
	char *newUser;
	char *newPassword;
	/*List* groupsList;*/

	/*
	if(NULL == (groupsList = ListCreate()))
	{
		free(newUser);
		free(newPassword);
		return NULL;
	}
	*/

	if (NULL == (newUserStruct = (User *)malloc(sizeof(User))))
	{
		free(newUser);
		free(newPassword);
		/*
		ListDestroy(&groupsList, NULL); TODO destroy Func
		*/
		return NULL;
	}

	strcpy(newUserStruct->m_username ,_newUser);
	strcpy(newUserStruct->m_password , _newPassword);
	newUserStruct->m_activeStatus = USER_DISCONNECTED;
	/*newUserStruct->m_groupsList = groupsList;*/

	return newUserStruct;
}