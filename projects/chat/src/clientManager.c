#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include "clientManager.h"
#include "clientNetwork.h"
#include "ui.h"
#include "chatProtocol.h" 
#include "chatMan.h"

#define MAX_TOTAL_LEN_MSG 256
#define MAGIC_NUM 0xFEEDFACE
#define UN_MAGIC_NUM 0xFEEEFEEE


struct ClientMan
{
    size_t m_magicNum;
    ChatMan* m_chat;
    ClientNet* m_clientNet;
};


#define PORT 8080
#define IP "0.0.0.0"


ClientResult ClientRegisterUser(ClientMan* _clientManager);


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
  if((clman->m_chat = ChatManCreate()) == NULL)
  {
    free(clman);
    perror("Clienet create err\n");
    return NULL;
  }
  if( ClientNetConnect(clman->m_clientNet, GetPort(clman->m_clientNet), GetIp(clman->m_clientNet))!=CLIENTNET_OK)
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
  int answer;

  answer = UIOpening();
  while(answer)
  {
    switch (answer)
    {
        case 1:
            printf("you chose to log in\n");
            ClientLoginUser(_clientMan);
            answer = 0;
            break; 
        case 2:
            printf("you chose to create user\n");
            ClientRegisterUser(_clientMan);
            answer = UIOpening();
            break;
        default:
            answer = UIOpening();
        continue;
    }

  }
  answer = UIOptions();
  while(answer)
  {
      switch (answer)
      {
        case 1:
            break;
        case 2:
            break;
        case 3:

            
            ClientJoinGrpReq(_clientMan);

      
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            break;
      }
  }
} 

ClientResult ClientRegisterUser(ClientMan* _clientManager)
{
    char msg[MAX_TOTAL_LEN_MSG];
    char returnMsg[MAX_TOTAL_LEN_MSG];
    RegRequest regRequest;
    RegReply regReply;

    UIRegisterUser(&regRequest);
    
    RegRequestPack(&regRequest, msg);


    ClientNetSend(_clientManager -> m_clientNet, msg, sizeof(msg));
    
    ClientNetRecieve(_clientManager -> m_clientNet, returnMsg, MAX_TOTAL_LEN_MSG);
    
    RegReplyUnpack(&regReply, returnMsg);
   
    UIPrintRegResponse(&regReply);
   
    return CLIENT_SUCCESS; 
}

ClientResult ClientLoginUser(ClientMan* _clientManager)
{
    char msg[MAX_TOTAL_LEN_MSG];
    char returnMsg[MAX_TOTAL_LEN_MSG];
    LogInRequest loginRequest;
    LogInReply loginReply;

    UILoginUser(&loginRequest);
    
    LogInRequestPack(&loginRequest, msg);

    ClientNetSend(_clientManager -> m_clientNet, msg, sizeof(msg));
    
    ClientNetRecieve(_clientManager -> m_clientNet, returnMsg, MAX_TOTAL_LEN_MSG);
    
    LogInReplyUnpack(&loginReply, returnMsg);
   
    UIPrintLoginResponse(&loginReply);

    return CLIENT_SUCCESS; /* TODO TODO TODO */ 
}

ClientResult ClientLogoutUser(ClientMan* _clientManager)
{
    char msg[MAX_TOTAL_LEN_MSG];
    char returnMsg[MAX_TOTAL_LEN_MSG];
    LogOutRequest logoutRequest;
    LogOutReply logoutReply;

    UILogoutUser(&logoutRequest);
    
    LogOutRequestPack(&logoutRequest, msg);
    
    ClientNetSend(_clientManager -> m_clientNet, msg, sizeof(msg));
    
    ClientNetRecieve(_clientManager -> m_clientNet, returnMsg, MAX_TOTAL_LEN_MSG);
    
    LogOutReplyUnpack(&logoutReply, returnMsg);
   
    UIPrintLogoutResponse(&logoutReply);
   
    return CLIENT_SUCCESS; 
}

ClientResult ClientJoinGrpReq(ClientMan* _clientManager)
{
    char msg[MAX_TOTAL_LEN_MSG];
    char returnMsg[MAX_TOTAL_LEN_MSG] = {1};
    JoinGrpRequest JoinGrp;
    JoinGrpReply GrpReply;
    int port = 0;
    int size = 0;
    char groupIP[16];/*todododo define*/

    UIGrpName(&JoinGrp);
    
    JoinGrpRequestPack(&JoinGrp, msg);
    size = sizeof(msg);
    printf("msg = %s\n", msg);
    ClientNetSend(_clientManager -> m_clientNet, msg , size - 1);
    
    
    ClientNetRecieve(_clientManager -> m_clientNet, returnMsg, MAX_TOTAL_LEN_MSG);
    
    JoinGrpReplyUnpack(&GrpReply, returnMsg);
   
    UIPrintJoinGrpResponse(&GrpReply);

    port = atoi(GrpReply.m_mcastPort);
     
    strcpy(groupIP, GrpReply.m_mcastIP);
    printf("ip == %s\n", groupIP);
    ChatManOpenChat(_clientManager -> m_chat, groupIP, port, GrpReply.m_username);
   
    return CLIENT_SUCCESS; 
}