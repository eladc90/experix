#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../inc/ClientNet.h"

typedef struct sockaddr_in  sockaddr_in;


#define LENGTH 	500
#define MAGIC	0xBEEFBEEF
#define MAGICDEAD  0xDEADBEEF


struct ClientNet
{
	size_t      m_magic;
	int		    m_socket;
	char*	    m_ip;
	int         m_port;
  	sockaddr_in m_serverAddr;
};



ClientNet* ClientNetCreate()
{
	ClientNet* client;

	client = (ClientNet*)malloc(sizeof(ClientNet));
	if(NULL == client)
	{
		return NULL;
	}

	client->m_socket = 0;
	client->m_port   = 0;
	client->m_ip	 = NULL;
 	client->m_magic	 = MAGIC;

	return client;
}

void ClientNetDestroy(ClientNet** _clientNet)
{
  if(!_clientNet || !(*_clientNet) || (*_clientNet)->m_magic != m_magic)
  {
    return;
  }

  (*_clientNet)->m_magic = MAGICDEAD;
  free(*_clientNet);
  *_clientNet = NULL;
}


ClientNetRes ClientNetConnect(ClientNet* _clientNet, size_t _port, const char* _ip)
{
	struct sockaddr_in sin;
	int soc = 0;

	if((!_clientNet) || (_clientNet->m_magic != MAGIC) || (_port < 1025) || (!_ip) )
	{
		return CLIENTNET_NOT_INIT_ERR;
	}

	_clientNet->m_port  = _port;
	_clientNet->m_ip	= (char*)_ip;

	if((soc = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		return CLIENTNET_ALLOC_ERR;
	}
	_clientNet->m_socket = soc;
	memset(&sin,0,sizeof(struct sockaddr_in));
	sin.sin_family 			 = AF_INET;
	sin.sin_port 			 = htons(_clientNet->m_port);
	sin.sin_addr.s_addr		 = inet_addr(_clientNet->m_ip);
	if(connect(_clientNet->m_socket,(struct sockaddr*)&sin, sizeof(sin)) < 0)
	{
		return CLIENTNET_NET_ERR;
	}
	_clientNet->m_serverAddr = sin;

	return CLIENTNET_OK;
}


ClientNetRes ClientNetDisConnect(ClientNet* _clientNet)
{
	if((!_clientNet) || (_clientNet->m_magic != MAGIC))
	{
		return CLIENTNET_NOT_INIT_ERR;
	}
	close(_clientNet->m_socket);
	_clientNet->m_ip		= NULL;
	_clientNet->m_port      = 0;
	_clientNet->m_socket	= 0;
	_clientNet->m_port		= 0;
	return CLIENTNET_SUCCESS;
}


ClientNetRes ClientNetSend(ClientNet* _clientNet, const char* _msg, size_t _size)
{
	if((!_message) || (!_clientNet) || (_clientNet->m_magic != MAGIC))
	{
		return CLIENTNET_NOT_INIT_ERR;
	}

	if(!_clientNet->m_socket)
	{
		return CLIENTNET_NET_ERR;
	}

	if(0 > sendto(_clientNet->m_socket, _msg, _size, 0, (struct sockaddr*)(&_clientNet->m_serverAddr), sizeof(_clientNet->m_serverAddr)))
	{
		return CLIENTNET_NET_ERR;
	}
	return CLIENTNET_OK;
}


ClientNetRes ClientNetRecieve(ClientNet* _clientNet, char* _buff, size_t _len)
{
	struct sockaddr_in sin = {0};
	int sokLen=sizeof(sin);

	if((!_buff) || (_len == 0) || (!_clientNet) || (_clientNet->m_magic != MAGIC))
	{
		return CLIENTNET_NOT_INIT_ERR;
	}

	if(!_clientNet->m_socket)
	{
		return CLIENTNET_NET_ERR;
	}

	if(_len >= LENGTH)
	{
		return CLIENTNET_ALLOC_ERR;
	}

	memset(&sin, 0, sizeof(struct sockaddr_in));
	sin.sin_family 		  	= AF_INET;
	sin.sin_port 		    = htons(_clientNet->m_port);
	sin.sin_addr.s_addr 	= inet_addr(_clientNet->m_ip);
	sokLen = sizeof(sin);

	if(recvfrom(_clientNet->m_socket, _buff, _len, 0, (struct sockaddr*)&sin,(socklen_t *)&sokLen)) <= 0)
	{
		ClientNetDisConnect(_clientNet);
	 	return CLIENTNET_NET_ERR;
	}
	return CLIENTNET_OK;
}


