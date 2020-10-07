#ifndef __SERVERNETWORK_H__
#define __SERVERNETWORK_H__
#include "../inc/list.h"
#include "../inc/list_itr.h"

/*-------------------------------------- typedefs --------------------------------------*/
typedef void (*OperationFunction)(const void* const _handler, const int _clientSockfd, const char *_msg);

typedef struct ServerNetwork
{
	size_t m_magicNumber;
	OperationFunction m_optFunc;
	void* m_handler;
	List *m_clientsLst;
}ServerNetwork;

/*------------------------------ Main Functions Declaration ------------------------------*/
ServerNetwork* ServerNetworkCreate(OperationFunction _optFunc, const void* const _handler);
void ServerNetworkDestroy(ServerNetwork* _serverNetwork);
void ServerNetworkRun(ServerNetwork* _serverNetwork);
void ServerNetworkStop(ServerNetwork* _serverNetwork);
int ServerNetworkSendMsg(char *_msgToClient, int _clientSock, size_t _size);

#endif /* __SERVERNETWORK_H__ */