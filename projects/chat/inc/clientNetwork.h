#ifndef __CLIENTNETWORK_H__
#define __CLIENTNETWORK_H__
#include <stddef.h>

typedef enum ClientNetRes{
	CLIENTNET_OK,
	CLIENTNET_NOT_INIT_ERR,
	CLIENTNET_ALLOC_ERR,
	CLIENTNET_NET_ERR
}ClientNetRes;

typedef struct ClientNet ClientNet;

/**
 * @brief  Create a new networking client 
 * @return ClientNet* pointer to the client  if success else NULL
 */
ClientNet* ClientNetCreate();


/**
 * @brief destroy  clientnet

 */
void ClientNetDestroy(ClientNet** _client);

/**
 * @brief Connect between Client to target server 
 *
 * @param _client :  the client that want to connect to server
 * @param _port	  :	 Port of the server
 * @param _ip	  :	 IP of ther server
 * @return CLIENT_ERR :
 */
ClientNetRes ClientNetConnect(ClientNet* _client, size_t _port, const char* _ip);

/**
 * @brief  this func sent message to the server

 */
ClientNetRes ClientNetSend(ClientNet* _client, const char* _msg, size_t _size);

/**
 * @brief this func receive a message from the server 
 
 */
ClientNetRes  ClientNetRecieve(ClientNet* _ClientNet, char* _buff, size_t _len);

/**
 * @brief disconnect this client from server

 */
ClientNetRes ClientNetDisConnect(ClientNet* _client);


char* GetIp(ClientNet* _cliNet);


int GetPort(ClientNet* _cliNet);

#endif /* __CLIENTNETWORK_H__ */