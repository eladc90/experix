#include <stdio.h>
#include <string.h>
#include <stdlib.h>   
#include "../inc/UserInterface.h"


#define TRUE 1
#define FALSE 0
#define LENGTH 500

struct UserOp
{
  char m_group[LENGTH];
  int  m_option;
};


User UserInterOpenening()
{
	User user;
	char password[LENGTH];
	char username[LENGTH];

	int new;
  
  printf("Welcome To REM CHAT\n\n Choose an option:\n");
	printf("1. Log In\n");
	printf("2. For New users: Regist\n");
	scanf("%d", &new);
  if(new==2)
  {
    User.regist=TRUE;
  }
	printf("Enter  Username: \n");
	scanf("%s", username);
	printf("Enter  password: \n");
	scanf("%s", password);

	strcpy(user.m_username, username);
	strcpy(user.m_password, password);

	return user;
}


UserOp UserInterOptions(const char* _username)
{
  UserOp Userop;
  char group[LENGTH];
  Userop.m_option = -1;
  int opt;

  printf("\n Choose one of the options:\n");
  printf("1. Create a new group\n");
  printf("2. Show all Groups\n");
  printf("3. Join a  Group\n");
  printf("4. Leave a group\n");
  printf("5. Log Out of Chat \n");
  printf("6. Enter To Chat Group\n");

  scanf("%d", &opt);



  switch(opt)
  {
    case 1:
      Userop.m_option =  ;
      printf("\n");
      scanf("%s", group);
      strcpy(Userop.m_group, group);
      break;
    case 2:
      Userop.m_option =  ;
      printf("  \n");
      scanf("%s", group);
      strcpy(Userop.m_group, group);
      break;
    case 3:
      Userop.m_option =  ;
      printf(" \n");
      scanf("%s", group);
      strcpy(Userop.m_group, group);
      break;
    case 4:
      Userop.m_option = ;
      break;
    case 5:
      Userop.m_option = ;
			break;
    case 6 :
      Userop.m_option = ;
      break;
    case 7:
      Userop.m_option =  ;
      break;
    default:
      Userop.m_option = FAlSE;
      break;
  }
  return op;
}


void UserRegist(RegRequest* _regist)
{
    scanf("%s", _regist -> m_username);
    scanf("%s", _regist -> m_password);
    _regist -> m_usernameLen = strlen(_regist -> m_username);
    _regist -> m_passwordLen = strlen(_regist -> m_password);
}

void PrintRegResponse(RegReply* reply)
{
    switch(reply -> m_requestStatus)
    {
        case USERNAME_ALREADY_EXISTS:
            printf("userName already exist\n");
            break;
        
        case OK:
            printf("user registeration succeed\n");
            break;

        default:
            printf("problem!! default\n");
            break;
}


/* -------------------------------------------------- */
void UserInterAns(int _msgType , List* _list)
{
    
}

/* -------------------------------------------------- */
