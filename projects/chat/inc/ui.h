#ifndef __UI_H__
#define __UI_H__

#include "../inc/chatProtocol.h"
#include "../inc/list.h"
#include "../inc/list_itr.h"
#include "../inc/list_functions.h"

#define LENGTH 500

int UIOpening();

int UIOptions();

void UIAns(int _msgType, List* _list);

void UIRegisterUser(RegRequest* _regReq);

void UIPrintRegResponse(RegReply* _regReply);

void UILoginUser(LogInRequest* _loginReq);

void UIPrintLoginResponse(LogInReply* _loginReply);

void UILogoutUser(LogOutRequest* _logoutReq);

void UIPrintLogoutResponse(LogOutReply* _logoutReply);

void UIGrpName(JoinGrpRequest* _JoinGrpRequest);

void UIPrintJoinGrpResponse(JoinGrpReply* _joinGrpReply);

#endif /* __UI_H__ */