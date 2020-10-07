#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include "../inc/list.h"
#include "../inc/list_itr.h"
#include "../inc/serverNetwork.h"


#define MAGIC_NUMBER 0xBEEFBEEF
#define DEAD_MAGIC_NUMBER 0xDEADBEEF
#define LOCALHOST "127.0.0.1"
#define PORT 8080
#define BACKLOG 500
#define MAXLINE 257
#define FALSE 0
#define TRUE 1
#define ABORT -1
#define SUCCESS 0
#define CANT_ADD_CLIENTS -2
#define MAX_CLIENTS 1000
#define MIN_FDS 2
#define MAX_FDS 1024

static int g_serverRun = TRUE;

/*------------------------------ Help Functions Declaration ------------------------------*/
static int InitServer(struct sockaddr_in* _servSin, struct sockaddr_in* _clientSin);
static void SetSigInt();
static void SigIntHandler(int _sig);
static void CheckNew(List* _clientsLst, struct sockaddr_in* _clientSin, int _listenSock, fd_set* _masterfd);
static int ConnectClient(List* _clientsLst, struct sockaddr* _clientSin, int _listenSock);
static void CheckCurrentClients(ServerNetwork* _serverNetwork, char* _buffer, fd_set* _masterfd, fd_set* _tmpfd, int _activity);
static int ReceiveFromClient(ServerNetwork* _serverNetwork, char* _buffer, int _clientSock);
static int SendToClient(char *_msgToClient, int _clientSock, size_t _size);
static void DisconnectClient(ListItr _itr, int _clientSock, fd_set* _masterfd);
static void DisconnectAllClients(List* _clientsLst, fd_set* _masterfd);
static void ListElementDestroy(void* _elem);

/*------------------------------ Main Functions Implementation ------------------------------*/
ServerNetwork* ServerNetworkCreate(OperationFunction _optFunc, const void* const _handler)
{
    ServerNetwork* newServerNetwork;
    List* clientsLst;

    if(NULL == _optFunc || NULL == _handler)
    {
        return NULL;
    }

    if(NULL == (clientsLst = ListCreate()))
    {
        return NULL;
    }

    if(NULL == (newServerNetwork = (ServerNetwork *)malloc(sizeof(ServerNetwork))))
    {
        ListDestroy(&clientsLst, ListElementDestroy);
        return NULL;
    }

    newServerNetwork->m_clientsLst = clientsLst;
    newServerNetwork->m_optFunc = _optFunc;
    newServerNetwork->m_handler = (void *)_handler;
    newServerNetwork->m_magicNumber = MAGIC_NUMBER;

    return newServerNetwork;
}

void ServerNetworkDestroy(ServerNetwork* _serverNetwork)
{
    if (NULL != _serverNetwork && MAGIC_NUMBER == _serverNetwork->m_magicNumber)
    {
        _serverNetwork->m_magicNumber = DEAD_MAGIC_NUMBER;
		ListDestroy(&_serverNetwork->m_clientsLst, ListElementDestroy);
        free(_serverNetwork);
    }
}

void ServerNetworkRun(ServerNetwork* _serverNetwork)
{
    struct sockaddr_in serverSin, clientSin;
    int listeningSock;
    char buffer[MAXLINE] = {0};
    fd_set masterfds, tmpfds;
    int activity;

    if(NULL != _serverNetwork && MAGIC_NUMBER == _serverNetwork->m_magicNumber)
    {
        listeningSock = InitServer(&serverSin, &clientSin);
        SetSigInt();

        FD_ZERO(&masterfds);
        FD_SET(listeningSock, &masterfds);
        while (g_serverRun)
        {
            tmpfds = masterfds;

            activity = select(MAX_FDS, &tmpfds, NULL, NULL, NULL);
            
            if (activity < 0)
            {
                printf("select error\n");
            }
            else if(activity > 0)
            {
                if (FD_ISSET(listeningSock, &tmpfds))
                {
                    CheckNew(_serverNetwork->m_clientsLst, &clientSin, listeningSock, &masterfds);
                    activity--;
                }
                if(activity)
                {
                    CheckCurrentClients(_serverNetwork, buffer, &masterfds, &tmpfds, activity);
                }
            }
        }

        DisconnectAllClients(_serverNetwork->m_clientsLst, &masterfds);
        close(listeningSock);
        ListDestroy(&_serverNetwork->m_clientsLst, ListElementDestroy);
    }
}

void ServerNetworkStop(ServerNetwork* _serverNetwork)
{

}

int ServerNetworkSendMsg(char *_msgToClient, int _clientSock, size_t _size)
{
    if(NULL != _msgToClient && _clientSock > MIN_FDS && _clientSock <= MAX_FDS)
    {
        SendToClient(_msgToClient, _clientSock, _size);
        return SUCCESS;
    }
    return ABORT;/* TODO */
}

/*------------------------------ Help Functions Implementation ------------------------------*/
static int InitServer(struct sockaddr_in* _servSin, struct sockaddr_in* _clientSin)
{
    int listeningSock;
    int optval = 1;

    if ((listeningSock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error creating socket!\n");
        exit(1);
    }

    memset(_servSin, 0, sizeof(struct sockaddr_in));
    _servSin->sin_family = AF_INET;
    _servSin->sin_addr.s_addr = inet_addr(LOCALHOST);
    _servSin->sin_addr.s_addr = INADDR_ANY;
    _servSin->sin_port = htons(PORT);

    memset(_clientSin, 0, sizeof(struct sockaddr_in));
    _clientSin->sin_family = AF_INET;
    _clientSin->sin_addr.s_addr = inet_addr(LOCALHOST);
    _clientSin->sin_addr.s_addr = INADDR_ANY;
    _clientSin->sin_port = htons(PORT);

    if (setsockopt(listeningSock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("reuse failed(server)");
        exit(1);
    }

    if ((bind(listeningSock, (struct sockaddr *)_servSin, sizeof(struct sockaddr_in)) < 0))
    {
        perror("Error binding!\n");
        exit(1);
    }

    if (listen(listeningSock, BACKLOG) < 0)
    {
        perror("Error Listening!\n");
        exit(1);
    }
    printf("Waiting for connections...\n");

    return listeningSock;
}

static void SetSigInt()
{
	struct sigaction SigAct;
	
	SigAct.sa_handler = SigIntHandler;
	SigAct.sa_flags = 0;
	sigemptyset(&SigAct.sa_mask);
	
	if (sigaction(SIGINT, &SigAct, NULL) == -1)
	{
		perror("sigaction() failed\n");
		exit(1);
	}
}

static void SigIntHandler(int _sig)
{
    g_serverRun = FALSE;
}

static void CheckNew(List* _clientsLst, struct sockaddr_in* _clientSin, int _listenSock, fd_set* _masterfd)
{
    int clientSock;

    if(ABORT == (clientSock = ConnectClient(_clientsLst, (struct sockaddr *)_clientSin, _listenSock)))
    {
        exit(1);
    }
    else if(CANT_ADD_CLIENTS == clientSock)
    {
        printf("\nSorry, No room for more connections.\n");
    }
    else
    {
        FD_SET(clientSock, _masterfd);
        printf("\nNew connection established! socketfd: %d, IP: %s, Port: %d.\n\n", 
                                                clientSock, inet_ntoa(_clientSin->sin_addr), ntohs(_clientSin->sin_port));
    }
}

static int ConnectClient(List* _clientsLst, struct sockaddr *_clientSin, int _listenSock)
{
    socklen_t client_len = sizeof(struct sockaddr_in);
    int clientSock;
    int* newSock;

    clientSock = accept(_listenSock, _clientSin, &client_len);
    if (clientSock < 0)
    {
        perror("Error accepting new clients!\n");
        return ABORT;
    }

    if(clientSock > MAX_CLIENTS)
    {
        close(clientSock);
        return CANT_ADD_CLIENTS;
    }

    if(NULL == (newSock = (int *)malloc(sizeof(int))))
    {
        perror("Allocation at clientConnect failed\n");
        return ABORT;
    }

    *newSock = clientSock;

    if(LIST_SUCCESS != ListPushTail(_clientsLst, newSock))
    {
        perror("Error at ListPushTail\n");
        return ABORT;
    }

    return clientSock;
}

static void CheckCurrentClients(ServerNetwork* _serverNetwork, char* _buffer, fd_set* _masterfd, fd_set* _tmpfd, int _activity)
{
    ListItr itr = ListItrBegin(_serverNetwork->m_clientsLst);
    ListItr itrEnd = ListItrEnd(_serverNetwork->m_clientsLst);
    int clientSock;
    int result;
    size_t listSize = ListSize(_serverNetwork->m_clientsLst);
    while(_activity != 0 /*TODO itr equal */)
    {
        printf("loop\n");
        clientSock = *((int *)ListItrGet(itr));
        if(FD_ISSET(clientSock, _tmpfd))
        {
            if (ABORT == (result = ReceiveFromClient(_serverNetwork, _buffer, clientSock)))
            {
                DisconnectClient(itr, clientSock, _masterfd);
            }
            _activity--;
        printf("this is the buffer %s\n",_buffer );
        }
        itr = ListItrNext(itr);
    }
}

static int ReceiveFromClient(ServerNetwork* _serverNetwork, char *_buffer, int _clientSock)
{
    int nBytes;

    nBytes = recv(_clientSock, _buffer, MAXLINE - 1, 0);
    if (0 >= nBytes)
    {
        printf("\nReceived 0 From Client #%d\n", _clientSock);
        /* _serverNetwork->m_optFunc(_serverNetwork->m_handler, _clientSock, NULL); */
        return ABORT;
    }

    _serverNetwork->m_optFunc(_serverNetwork->m_handler, _clientSock, _buffer);
    return SUCCESS;
}

static int SendToClient(char *_msgToClient, int _clientSock, size_t _size)
{
    if (send(_clientSock, _msgToClient, _size, 0) < 0)/*TODO*/
    {
        perror("Error sending in server!\n");
        return ABORT;
    }
    return SUCCESS;
}

static void DisconnectClient(ListItr _itr, int _clientSock, fd_set* _masterfd)
{
    ListItr tmpItr;

    printf("Disconnecting Client #%d\n\n", _clientSock);
    close(_clientSock);
    tmpItr = ListItrPrev(_itr);
    ListItrRemove(_itr);
    _itr = tmpItr;
    FD_CLR(_clientSock, _masterfd);
}

static void DisconnectAllClients(List* _clientsLst, fd_set* _masterfd)
{
    ListItr itr = ListItrBegin(_clientsLst);

    while(!ListItrEquals(itr, ListItrEnd(_clientsLst)))
    {
        DisconnectClient(itr, *(int*)ListItrGet(itr), _masterfd);
        itr = ListItrNext(itr);
    }
}

static void ListElementDestroy(void* _elem)
{
	free(_elem);
}