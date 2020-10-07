#ifndef __CLIENTMANAGER_H__
#define __CLIENTMANAGER_H__
#include "../inc/chatProtocol.h"

typedef struct ClientMan ClientMan;

typedef enum ClientResult
{
	CLIENT_SUCCESS,			/* Successful operation */
	CLIENT_FAILURE,			/* Unsuccessful operation */
	CLIENT_USER_ALREADY_EXISTS,
	CLIENT_USER_DOESNT_EXIST,
	CLIENT_USER_WRONG_PASSWORD,
	CLIENT_USER_ALREADY_CONNECTED,
	CLIENT_USER_DISCONNECTED
} ClientResult;

/**
 * @brief  Create a ClientManager   
 * @return ClientMan* if Successd else NULL
 */
ClientMan* ClientManCreate();

/**
 * @brief Running application of this client 
 * @param _clientMan : ClientMan pointer to make run
 */
void ClientManRun(ClientMan* _clientMan);

/**
 * @brief Destroy the client (all)
 * @param _clientMan : pointer to the client 
 */
void ClientManDestroy(ClientMan* _clientMan);

ClientResult ClientRegisterUser(ClientMan* _clientManager);

ClientResult ClientLoginUser(ClientMan* _clientManager);

ClientResult ClientLogoutUser(ClientMan* _clientManager);

ClientResult ClientJoinGrpReq(ClientMan* _clientManager);


#endif /* __CLIENTMANAGER_H__ */