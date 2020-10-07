#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <string.h>
#include "../inc/serverManager.h"
#include "../inc/chatProtocol.h"
#include "../inc/ChatProtocolLimits.h"
#include "../inc/serverNetwork.h"
#include "../inc/userManager.h"
/*#include "groupManager.h"*/

#define MAGIC_NUMBER 0xBEEFBEEF
#define DEAD_MAGIC_NUMBER 0xDEADBEEF
#define MIN_FDS 2
#define MAX_FDS 1024
#define FILE_PATH "./registeredUsers.txt"

/*------------------------------ Help Functions Declaration ------------------------------*/
static void RequestFunction(const void* const _handler, const int _clientSockfd, const char *_msg);
/* static void SaveUsersToFile(ServerManager* _serverManager); */

static ServerResult UserManagerAddToGroup(const char* _groupName, GroupMng* _maneger);

/*------------------------------ Main Functions Implementation ------------------------------*/
ServerManager* ServerManagerCreate()
{
	ServerManager* newServerManager;
	ServerNetwork* newServerNetwork;
	UserManager* newUserManager;
	GroupMng* newGroupManager;

	if(NULL == (newServerManager = (ServerManager *)malloc(sizeof(ServerManager))))
	{
		return NULL;
	}
	if (NULL == (newGroupManager = GroupMngCreate()))
	{
		free(newServerManager);
		return NULL;
	}

	if(NULL == (newServerNetwork = ServerNetworkCreate(RequestFunction, newServerManager)))
	{
		free(newServerManager);
		return NULL;
	}

	if(NULL == (newUserManager = UserManagerCreate()))
	{
		free(newServerManager);
		ServerNetworkDestroy(newServerNetwork);
		return NULL;
	}

	newServerManager->m_groupManager = newGroupManager;
	newServerManager->m_serverNetwork = newServerNetwork;
	newServerManager->m_userManager = newUserManager;
	newServerManager->m_groupManager = newGroupManager;
	newServerManager->m_magicNumber = MAGIC_NUMBER;

	
	/*
	if(NULL == (newGroupManager = GroupManagerCreate()))
	{
		free(newServerManager);
		ServerNetworkDestroy(newServerNetwork);
		UserManagerDestroy(newUserManager);
		return NULL;
	}
	*/
	return newServerManager;
}

void ServerManagerDestroy(ServerManager* _serverManager)
{
	if (NULL != _serverManager && MAGIC_NUMBER == _serverManager->m_magicNumber)
    {
		/* SaveUsersToFile(_serverManager); */
        _serverManager->m_magicNumber = DEAD_MAGIC_NUMBER;
		ServerNetworkDestroy(_serverManager->m_serverNetwork);
		UserManagerDestroy(_serverManager->m_userManager);
		/*GroupManagerDestroy(_serverManager->m_groupManager);*/
        free(_serverManager);
    }
}

void ServerManagerRun(ServerManager* _serverManager)
{
	ServerNetworkRun(_serverManager->m_serverNetwork);
	return;
}

void ServerRegisterUser(ServerManager* _serverManager, const int _clientSockfd, const char *_msg)
{
	UserManagerResult userManagerResult;
	RegRequest regUserRequest;
	RegReply regUserReply;
	char replyToClient[MAX_TOTAL_LEN_MSG];

	if(NULL == _serverManager || NULL == _msg || _clientSockfd <= MIN_FDS || _clientSockfd > MAX_FDS)
	{
		regUserReply.m_requestStatus = GENERAL_ERROR;
		RegReplyPack(&regUserReply, replyToClient);
		ServerNetworkSendMsg(replyToClient, _clientSockfd, replyToClient[1] + 2);
		return;
	}
	RegRequestUnpack(&regUserRequest, _msg);

	userManagerResult = UserManagerAdd(_serverManager->m_userManager, regUserRequest.m_username, regUserRequest.m_password);
	if(USERM_SUCCESS == userManagerResult)
	{
		printf("ok\n");
		regUserReply.m_requestStatus = OK;
	}
	else if(USERM_UNINITIALIZED_PTRS == userManagerResult || USERM_FAILURE == userManagerResult)
	{
		printf("not ok\n");
		regUserReply.m_requestStatus = GENERAL_ERROR;
	}
	else if(USERM_ALREADY_EXISTS == userManagerResult)
	{
		printf("not ok\n");
		regUserReply.m_requestStatus = USERNAME_ALREADY_EXISTS;
	}
	RegReplyPack(&regUserReply, replyToClient);
	printf("this is what server replay to client  *%s\n", replyToClient);
	ServerNetworkSendMsg(replyToClient, _clientSockfd, replyToClient[1] + 2);
	return;
}

void ServerLogInUser(ServerManager* _serverManager, const int _clientSockfd, const char *_msg)
{
	UserManagerResult userManagerResult;
	LogInRequest loginUserRequest;
	LogInReply loginUserReply;

	char replyToClient[MAX_TOTAL_LEN_MSG];

	if(NULL == _serverManager || NULL == _msg || _clientSockfd <= MIN_FDS || _clientSockfd > MAX_FDS)
	{
		loginUserReply.m_requestStatus = GENERAL_ERROR;
		LogInReplyPack(&loginUserReply, replyToClient);
		ServerNetworkSendMsg(replyToClient, _clientSockfd, replyToClient[1] + 2);
		return;
	}
	LogInRequestUnpack(&loginUserRequest, _msg);
	printf("user = %s pass == %s\n", loginUserRequest.m_username,loginUserRequest.m_password);
	userManagerResult = UserManagerLogin(_serverManager->m_userManager, loginUserRequest.m_username, loginUserRequest.m_password);
	if(USERM_SUCCESS == userManagerResult)
	{
		printf("ok\n");
		loginUserReply.m_requestStatus = OK;
	}
	else if(USERM_UNINITIALIZED_PTRS == userManagerResult)
	{
		printf("not ok\n");
		loginUserReply.m_requestStatus = GENERAL_ERROR;
	}
	else if(USERM_DOESNT_EXIST == userManagerResult)
	{
		printf("not ok\n");
		loginUserReply.m_requestStatus = USERNAME_DOESNT_EXIST;
	}
	else if(USERM_ALREADY_CONNECTED == userManagerResult)
	{
		printf("not ok\n");
		loginUserReply.m_requestStatus = USER_ALREADY_CONNECTED;
	}
	else
	{
		printf("not ok\n");
		loginUserReply.m_requestStatus = WRONG_PASSWORD;
	}

	LogInReplyPack(&loginUserReply, replyToClient);
	printf("this is char *%s\n", replyToClient);
	ServerNetworkSendMsg(replyToClient, _clientSockfd, replyToClient[1] + 2);
	return;
}

void ServerLogOutUser(ServerManager* _serverManager, const int _clientSockfd, const char *_msg)
{
	UserManagerResult userManagerResult;
	LogOutRequest logoutUserRequest;
	LogOutReply logoutUserReply;
	char replyToClient[MAX_TOTAL_LEN_MSG];

	if(NULL == _serverManager || NULL == _msg || _clientSockfd <= MIN_FDS || _clientSockfd > MAX_FDS)
	{
		logoutUserReply.m_requestStatus = GENERAL_ERROR;
		LogOutReplyPack(&logoutUserReply, replyToClient);
		ServerNetworkSendMsg(replyToClient, _clientSockfd, replyToClient[1] + 2);
		return;
	}
	LogOutRequestUnpack(&logoutUserRequest, _msg);

	userManagerResult = UserManagerLogout(_serverManager->m_userManager, logoutUserRequest.m_username);
	if(USERM_SUCCESS == userManagerResult)
	{
		printf("ok\n");
		logoutUserReply.m_requestStatus = OK;
	}
	else if(USERM_UNINITIALIZED_PTRS == userManagerResult)
	{
		printf("not ok\n");
		logoutUserReply.m_requestStatus = GENERAL_ERROR;
	}
	
	
	
	/*
	else if(USERM_DOESNT_EXIST == userManagerResult)
	{
		printf("not ok\n");
		logoutUserReply.m_requestStatus = USERNAME_DOESNT_EXIST;
	}
	else if(USERM_DISCONNECTED == userManagerResult)
	{
		printf("not ok\n");
		logoutUserReply.m_requestStatus = LOGOUT_FAILED;
	}
	*/

	LogOutReplyPack(&logoutUserReply, replyToClient);
	printf("this is char *%s\n", replyToClient);
	ServerNetworkSendMsg(replyToClient, _clientSockfd, replyToClient[1] + 2);
	return;
}

ServerResult ServerCreateGroup(ServerManager* _serverManager, const int _clientSockfd, const char *_msg);
ServerResult ServerGetGroups(ServerManager* _serverManager, const int _clientSockfd, const char *_msg);

void ServerJoinGroup(ServerManager* _serverManager, const int _clientSockfd, const char *_msg)
{
	UserManagerResult userManagerResult;
	JoinGrpReply GrpReply;
	JoinGrpRequest GrpRequest;
	char replyToClient[MAX_TOTAL_LEN_MSG];
	char groupIp[16];/*TODO*/
	int groupPort = 0;/*TODO*/

	if(NULL == _serverManager || NULL == _msg || _clientSockfd <= MIN_FDS || _clientSockfd > MAX_FDS)
	{
		GrpReply.m_requestStatus = GENERAL_ERROR;
		JoinGrpReplyPack(&GrpReply, replyToClient);
		ServerNetworkSendMsg(replyToClient, _clientSockfd, replyToClient[1] + 2);
		return;
	}



	JoinGrpRequestUnpack(&GrpRequest, _msg);
	userManagerResult = UserManagerAddToGroup(GrpRequest.m_username, _serverManager -> m_groupManager);
	if(SERVER_GRP_ALREADY_EXISTS == userManagerResult)
	{
		GrpReply.m_requestStatus = OK;
		strcpy(groupIp ,GetGroupIp(GrpRequest.m_groupName, _serverManager -> m_groupManager));/*TODO check NULL */
		groupPort = GetGroupPort(GrpRequest.m_groupName, _serverManager -> m_groupManager);
		strcpy(GrpReply.m_mcastIP, groupIp);
		snprintf(GrpReply.m_mcastPort, sizeof(GrpReply.m_mcastPort), "%d", groupPort);
		GrpReply.m_mcastIPLen = strlen(GrpReply.m_mcastIP);
		GrpReply.m_mcastPortLen = strlen(GrpReply.m_mcastPort);
	}
	else if(USERM_GRP_NOT_EXIST == userManagerResult)
	{
		printf("not ok\n");
		GrpReply.m_requestStatus = GROUP_DOESNT_EXIST;
	}

	JoinGrpReplyPack(&GrpReply, replyToClient);
	ServerNetworkSendMsg(replyToClient, _clientSockfd, replyToClient[1] + 2);
	return;
}

ServerResult ServerLeaveGroup(ServerManager* _serverManager, LeaveGrpRequest _leaveGrpMsg);

/*------------------------------ Help Functions Implementation ------------------------------*/
static void RequestFunction(const void* const _handler, const int _clientSockfd, const char *_msg)
{
	char tag;

	tag = _msg[0];
	printf("%c option!\n", tag);
	switch(tag)
	{
		case REGISTRATION:
			ServerRegisterUser((ServerManager *)_handler, _clientSockfd, _msg);
			break;
		case LOG_IN:
			ServerLogInUser((ServerManager *)_handler, _clientSockfd, _msg);
			break;

		case JOIN_GROUP:
			ServerJoinGroup((ServerManager *)_handler, _clientSockfd, _msg);
			break;

		default:
			
			printf("Not an option!\n");
			break;
	}
}

/*
static void SaveUsersToFile(ServerManager* _serverManager)
{
	FILE* fpUsers;

	fpUsers = fopen(FILE_PATH, "w");
	if(NULL == fpUsers)
	{
		return ERR_FOPEN_FAILED;
	}

	while ()
	{
		
	}

	fprintf(fp2, "%s", buff);



}


static ServerResult UserManagerAddToGroup(const char* _groupName, GroupMng* _maneger)
{
	if (GroupDBAddUserToGroup(_groupName, _maneger) == GROUP_OK)
	{
		return SERVER_SUCCESS;
	}
	return SERVER_GRP_ALREADY_EXISTS;
}