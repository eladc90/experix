#ifndef __USERDB_H__
#define __USERDB_H__
#include <stddef.h> /* size_t */
#include "hashmap.h"

/*-------------------------------------- typedefs --------------------------------------*/
typedef struct User User;
typedef struct UserDB UserDB;

typedef enum UserDBResult
{
	USERDB_SUCCESS,			/* Successful operation */
	USERDB_FAILURE,			/* Unsuccessful operation */
	USERDB_UNINITIALIZED_PTRS,
	USERDB_ALREADY_EXISTS,
	USERDB_DOESNT_EXIST,
	USERDB_WRONG_PASSWORD,
	USERDB_RIGHT_PASSWORD,
	USERDB_ALREADY_CONNECTED,
	USERDB_DISCONNECTED
} UserDBResult;

typedef enum ActivityStatus
{
	USER_DISCONNECTED,
	USER_CONNECTED
} ActivityStatus;

/*------------------------------ Main Functions Declaration ------------------------------*/
UserDB* UserDBCreate();
void UserDBDestroy(UserDB* _userDB);

UserDBResult UserDBAddUser(UserDB* _userDB, const char* _newUser, const char* _newPassword);
UserDBResult UserDBDeleteUser(UserDB* _userDB, const char* _username);
UserDBResult UserDBDoesUserExist(UserDB* _userDB, const char* _username);
UserDBResult UserDBCheckUserDetails(UserDB* _userDB, const char* _username, const char* _password);
UserDBResult UserDBIsUserActive(UserDB* _userDB, const char* _username);
void UserDBSetActivity(UserDB* _userDB, const char* _username, ActivityStatus _newActivity);

#endif /* __USERDB_H__ */