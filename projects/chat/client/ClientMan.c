#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 

#include "../inc/ClientMan.h"
#include "../inc/ClientNet.h"


/*
#include "../inc/UserInterface.h"
#include "../inc/Chat.h" */

#include "chatProtocol.h" 

#define MAX_TOTAL_LEN_MSG 256
#define MAGIC_NUM 0xFEEDFACE
#define UN_MAGIC_NUM 0xFEEEFEEE


struct ClientMan
{
  ClientNet*   m_clientNet;
  Chat*       m_chat;
};



typedef struct ClientMan
{
    size_t m_magicNum;
    ClientNet*   m_clientNet;

}ClientMan;


#define PORT ?
#define IP ?



/* -------------------------------------------------- */

ClientMan* ClientManCreate()
{
  ClientMan* clman = (ClientMan*) malloc(sizeof(ClientMan));
  if (NULL == clman)
  {
    return clman;
  }

  if(NULL == (clman->m_clientNet = ClientNetCreate()))
  {
    free(clman);
    perror("Clienet create err\n");
    return NULL;
  }

	if(NULL ==(clman->m_chat = /* ChatCreate() */  ))
  {
    perror("chat create err");
    ClientNetDestroy(&clman->m_clientNet);
		free(clman);
    return NULL;
  }

  if( ClientNetConnect(clman->m_clientNet, /* port, ip */)!=CLIENTNET_OK)
  {
    perror("Connection Failed");
    ClientNetDestroy(&clman->m_clientNet);
    /*ChatDestroy(clman->m_chat); */
    free(clman);
    return NULL;
  }

  return clman;
}

/* -------------------------------------------------- */

void ClientManDestroy(ClientMan* _clientMan)
{
  if( ClientNetDisConnect(_clientMan->m_clientNet)!=CLIENTNET_OK)
  {
    printf("Disconnect err\n");
    return;
  }

  ClientNetDestroy(&_clientMan->m_clientNet);
/* 	ChatDestroy(_clientMan->m_chat);
 */ 
 free(_clientMan);
}

/* -------------------------------------------------- */

void ClientManRun(ClientMan* _clientMan)
{
  char*buff[LENGTH]
  size_t len=;

  if(CLIENTNET_OK != ClientNetSend(_clientMan->m_clientNet, buff, len))
  {
    printf("Send from client err\n");
    return;
  }
	if (CLIENTNET_OK != ClientNetRecieve(_clientMan->m_clientNet, buff, LENGTH -1)
  {
    return;
  }
}


ClientResult ClientRegisterUser(ClientMan* _serverManager, RegRequest _regUserMsg)
{
    RegReply reply;
    char *msg[MAX_TOTAL_LEN_MSG];
    char *returnMsg[MAX_TOTAL_LEN_MSG];
    RegRequest regist;
    UserRegist(&regist);
    RegRequestPack(&regist, msg);
    ClientNetSend(_serverManager -> m_clientNet, &msg, strlen(msg));
    ClientNetRecieve(_serverManager -> m_clientNet, &returnMsg, MAX_TOTAL_LEN_MSG);
    RegReplyUnpack(&reply, returnMsg);
}