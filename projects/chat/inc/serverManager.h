#ifndef __SERVERMANAGER_H__
#define __SERVERMANAGER_H__
#include "../inc/chatProtocol.h"
#include "../inc/ChatProtocolLimits.h"
#include "../inc/serverNetwork.h"
#include "../inc/userManager.h"
#include "groupMng.h"
/*#include "groupManager.h"*/

/*-------------------------------------- typedefs --------------------------------------*/
typedef enum ServerResult
{
	SERVER_SUCCESS,			/* Successful operation */
	SERVER_FAILURE,			/* Unsuccessful operation */
	SERVER_UNINITIALIZED_PTRS,
	SERVER_USER_ALREADY_EXISTS,
	SERVER_GRP_ALREADY_EXISTS,
	SERVER_USER_DOESNT_EXIST,
	SERVER_USER_WRONG_PASSWORD,
	SERVER_USER_ALREADY_CONNECTED,
	SERVER_USER_DISCONNECTED
} ServerResult;

typedef struct ServerManager
{
	size_t m_magicNumber;
	ServerNetwork* m_serverNetwork;
	UserManager* m_userManager;
	GroupMng* m_groupManager;
}ServerManager;

typedef void (*RunRequestFunction)(const void* const _handler, const int _clientSockfd, const char *_msg);

/*------------------------------ Main Functions Declaration ------------------------------*/
ServerManager* ServerManagerCreate();
void ServerManagerDestroy(ServerManager* _serverManager);
void ServerManagerRun(ServerManager* _serverManager);

void ServerRegisterUser(ServerManager* _serverManager, const int _clientSockfd, const char *_msg);
void ServerLogInUser(ServerManager* _serverManager, const int _clientSockfd, const char *_msg);
void ServerLogOutUser(ServerManager* _serverManager, const int _clientSockfd, const char *_msg);
/*
ServerResult ServerCreateGroup(CreateGrpRequest _createGrpMsg);
ServerResult ServerGetGroups(GetGrpsRequest _getGrpsMsg);
ServerResult ServerJoinGroup(JoinGrpRequest _joinGrpMsg);
ServerResult ServerLeaveGroup(LeaveGrpRequest _leaveGrpMsg);
*/

#endif /* __SERVERMANAGER_H__ */