#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/ui.h"
#include "../inc/chatProtocol.h"

#define TRUE 1
#define FALSE 0
#define LENGTH 500

struct UserOp
{
  char m_group[LENGTH];
  int  m_option;
};

int UIOpening()
{
	int option;

    printf("Welcome To REM CHAT\n\n Choose an option:\n");
	printf("1. Log In\n");
	printf("2. For New users: Regist\n");
	scanf("%d", &option);
  
	return option;
}

int UIOptions()
{
  int opt;

  printf("\n Choose one of the options:\n");
  printf("1. Create a new group\n");
  printf("2. Show all Groups\n");
  printf("3. Join a  Group\n");
  printf("4. Leave a group\n");
  printf("5. Log Out of Chat \n");
  printf("6. Enter To Chat Group\n");
  scanf("%d", &opt);

  return opt;
}

void UIRegisterUser(RegRequest* _regReq)
{
    printf("enter you Username\n");
    scanf("%s", _regReq -> m_username);
    printf("enter you password\n");
    scanf("%s", _regReq -> m_password);
    _regReq -> m_usernameLen = strlen(_regReq -> m_username);
    _regReq -> m_passwordLen = strlen(_regReq -> m_password);
}

void UIPrintRegResponse(RegReply* _regReply)
{
    printf("this is the sts %c\n",_regReply -> m_requestStatus);
    switch(_regReply -> m_requestStatus)
    {
        case OK:
            printf("User registeration Succeed\n");
            break;

        case GENERAL_ERROR:
            printf("User registeration - General Error\n");
            break;

        case USERNAME_ALREADY_EXISTS:
            printf("Username already exists\n");
            break;

        default:
            printf("problem!! default\n");
            break;
    }
}

void UILoginUser(LogInRequest* _loginReq)
{
    printf("enter you Username\n");
    scanf("%s", _loginReq -> m_username);
    printf("enter you password\n");
    scanf("%s", _loginReq -> m_password);
    _loginReq -> m_usernameLen = strlen(_loginReq -> m_username);
    _loginReq -> m_passwordLen = strlen(_loginReq -> m_password);
}

void UIPrintLoginResponse(LogInReply* _loginReply)
{
    switch(_loginReply -> m_requestStatus)
    {
        case OK:
            printf("User login Succeed\n");
            break;

        case GENERAL_ERROR:
            printf("User login - General Error\n");
            break;

        case USERNAME_DOESNT_EXIST:
            printf("User login - Username doesn't exist\n");
            break;
        
        case USER_ALREADY_CONNECTED:
            printf("User login - User already connected\n");
            break;

        case WRONG_PASSWORD:
            printf("User login - Wrong password\n");
            break;

        default:
            printf("problem!! default\n");
            break;
    }
}

void UILogoutUser(LogOutRequest* _logoutReq)
{
    printf("enter you Username\n");
    scanf("%s", _logoutReq -> m_username);
}


void UIGrpName(JoinGrpRequest* _JoinGrpRequest)
{
    printf("enter you Username\n");
    scanf("%s", _JoinGrpRequest -> m_username);
    printf("enter group name\n");
    scanf("%s", _JoinGrpRequest -> m_groupName);
    _JoinGrpRequest -> m_usernameLen = strlen(_JoinGrpRequest -> m_username);
    _JoinGrpRequest -> m_groupNameLen = strlen(_JoinGrpRequest -> m_groupName);

}

void UIPrintLogoutResponse(LogOutReply* _logoutReply)
{
    printf("sts  = %d", (_logoutReply -> m_requestStatus - '0'));
    switch(_logoutReply -> m_requestStatus)
    {
        case OK:
            printf("User logout Succeed\n");
            break;

        case GENERAL_ERROR:
            printf("User logout - General Error\n");
            break;


            /*TODO Groups Error statuses*/

        default:
            printf("problem!! default\n");
            break;
    }
}

void UIPrintJoinGrpResponse(JoinGrpReply* _joinGrpReply)
{
 
    switch(_joinGrpReply -> m_requestStatus)
    {
        case OK:
            printf("User join group Succeed\n");
            break;

        case GROUP_DOESNT_EXIST:
            printf("group does not exist\n");
            break;

        default:
            printf("problem default\n");
            break;
    }
}