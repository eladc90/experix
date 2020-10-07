#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/ChatProtocolLimits.h"
#include "../inc/chatProtocol.h"
#define TAG 0
#define LEN 1
#define NAME_LEN 2
#define REQ_STS 2



/*--Registration--*/
ProtocolStatus RegRequestPack(const RegRequest* _request, char* _msg)
{
    int nameSize = _request -> m_usernameLen;
    int passSize = _request -> m_passwordLen;
    if (_request == NULL || _msg == NULL)
    {
        return PROTOCOL_FAIL;
    }
    _msg[TAG] = (char)REGISTRATION;
    _msg[LEN] = (char)(nameSize + passSize + 2);
    _msg[NAME_LEN] = (char)nameSize;
    memcpy(_msg + 3, _request -> m_username, nameSize);
    _msg[nameSize + 3] = _request -> m_passwordLen;
    memcpy(_msg + nameSize + 4, _request -> m_password, passSize);
    _msg[nameSize+passSize+4]='\0';
    return PROTOCOL_SUCCESS;
}

ProtocolStatus RegRequestUnpack (RegRequest* _request, const char* _msg)
{
    if (_request == NULL || _msg == NULL)
    {
        return PROTOCOL_FAIL;
    }
    _request -> m_usernameLen = _msg[REQ_STS];
    memcpy(_request -> m_username, _msg + 3, (size_t)(_request -> m_usernameLen));
    _request -> m_username[ _request -> m_usernameLen] = '\0';
    _request -> m_passwordLen = _msg[3 + (size_t)(_request -> m_usernameLen)];
    memcpy(_request -> m_password, _msg + (4 + (size_t)(_request -> m_usernameLen)), (size_t)(_request -> m_passwordLen));
    _request -> m_password[ _request -> m_passwordLen] = '\0';
    return PROTOCOL_SUCCESS;
}


ProtocolStatus RegReplyPack (const RegReply* _reply, char* _msg)
{
    if (_reply == NULL || _msg == NULL)
    {
        return PROTOCOL_FAIL;
    }
    _msg[TAG] = (unsigned char)REGISTRATION;
    _msg[LEN] = '1';
    _msg[2] = _reply -> m_requestStatus;
    _msg[3] = '\0';
    return PROTOCOL_SUCCESS;
}

ProtocolStatus RegReplyUnpack (RegReply* _reply, const char* _msg)
{
    if (_reply == NULL || _msg == NULL)
    {
        return PROTOCOL_FAIL;
    }
    _reply -> m_requestStatus = _msg[REQ_STS];
    return PROTOCOL_SUCCESS;
}

/*--LogIn--*/
ProtocolStatus LogInRequestPack (const LogInRequest* _request, char* _msg)
{
    int userLen = _request -> m_usernameLen;
    int passLen = _request -> m_passwordLen;

    if (_request == NULL || _msg == NULL)
    {
        return PROTOCOL_FAIL;
    }
    _msg[TAG] = (char)LOG_IN;
    _msg[LEN] = (char)(userLen + passLen + 2);
    _msg[NAME_LEN] = (char)userLen;
    memcpy(_msg + 3, _request -> m_username, userLen);
    _msg[3 + userLen] = (char)passLen;
    memcpy(_msg + 3 + userLen + 1, _request -> m_password, passLen);
    return PROTOCOL_SUCCESS;
}


ProtocolStatus LogInRequestUnpack (LogInRequest* _request, const char* _msg)
{
    int userLen = _msg[2];
    int passLen = _msg[3 + userLen];

    if (_request == NULL || _msg == NULL)
    {
        return PROTOCOL_FAIL;
    }
    _request -> m_usernameLen = _msg[REQ_STS];
    memcpy(_request -> m_username, _msg + 3, userLen);
    _request -> m_username[_request -> m_usernameLen] ='\0';
    _request -> m_passwordLen = _msg[3 + userLen];
    memcpy(_request -> m_password, _msg + 3 + userLen + 1, passLen);
    _request -> m_password[_request -> m_passwordLen] = '\0';

    return PROTOCOL_SUCCESS;
}

ProtocolStatus LogInReplyPack (const LogInReply* _reply, char* _msg)
{
    if (_reply == NULL || _msg == NULL)
    {
        return PROTOCOL_FAIL;
    }
    _msg[TAG] = (char)LOG_IN;
    _msg[LEN] = '1';
    _msg[NAME_LEN] = _reply -> m_requestStatus;
    return PROTOCOL_SUCCESS;
}

ProtocolStatus LogInReplyUnpack (LogInReply* _reply, const char* _msg)
{
    if (_reply == NULL || _msg == NULL)
    {
        return PROTOCOL_FAIL;
    }
    _reply -> m_requestStatus = _msg[2];
    return PROTOCOL_SUCCESS;
}

/*--CreateGroup--*/
ProtocolStatus CreateGrpRequestPack (const CreateGrpRequest* _request, char* _msg);
ProtocolStatus CreateGrpRequestUnpack (CreateGrpRequest* _request, const char* _msg);
ProtocolStatus CreateGrpReplyPack (const CreateGrpReply* _reply, char* _msg);
ProtocolStatus CreateGrpReplyUnpack (CreateGrpReply* _reply, const char* _msg);

/*--GetGroups--*/
ProtocolStatus GetGrpsRequestPack (/* const GetGrpsRequest* _request,*/ char* _msg);
ProtocolStatus GetGrpsRequestUnpack (/* GetGrpsRequest* _request,*/ const char* _msg);
ProtocolStatus GetGrpsReplyPack (const GetGrpsReply* _reply, char* _msg);
ProtocolStatus GetGrpsReplyUnpack (GetGrpsReply* _reply, const char* _msg);

/*--JoinGroup--*/


ProtocolStatus JoinGrpRequestPack (const JoinGrpRequest* _request, char* _msg)
{
    int userLen = _request -> m_usernameLen;
    int groupLen = _request -> m_groupNameLen;

    if (_request == NULL || _msg == NULL)
    {
        return PROTOCOL_FAIL;
    }
    _msg[TAG] = (char)JOIN_GROUP;
    _msg[LEN] = (char)(userLen + groupLen + 2);
    _msg[NAME_LEN] = (char)userLen;
    memcpy(_msg + 3, _request -> m_username, userLen);
    _msg[3 + userLen] = (char)groupLen;
    memcpy(_msg + 3 + userLen + 1, _request -> m_groupName, groupLen);
    _msg[userLen + groupLen + 4] = '\0';
    return PROTOCOL_SUCCESS;
}

ProtocolStatus JoinGrpRequestUnpack (JoinGrpRequest* _request, const char* _msg)
{
    if (_request == NULL || _msg == NULL)
    {
        return PROTOCOL_FAIL;
    }
    _request -> m_usernameLen = _msg[REQ_STS];
    memcpy(_request -> m_username, _msg + 3, (size_t)(_request -> m_usernameLen));
    _request -> m_username[ _request -> m_usernameLen] = '\0';
    _request -> m_groupNameLen = _msg[3 + (size_t)(_request -> m_usernameLen)];
    memcpy(_request -> m_groupName, _msg + (4 + (size_t)(_request -> m_usernameLen)), (size_t)(_request -> m_groupNameLen));
    _request -> m_groupName[ _request -> m_groupNameLen] = '\0';
    return PROTOCOL_SUCCESS;
}



ProtocolStatus JoinGrpReplyPack(const JoinGrpReply* _reply, char* _msg)
{
    int ipLen = _reply -> m_mcastIPLen;
    int portLen = _reply -> m_mcastPortLen;
    if (_reply == NULL || _msg == NULL)
    {
        return PROTOCOL_FAIL;
    }
    _msg[TAG] = (char)JOIN_GROUP;
    _msg[LEN] = (char)(ipLen + portLen + 3);
    _msg[NAME_LEN] = _reply -> m_requestStatus;
    _msg[3] = _reply -> m_mcastIPLen;
    memcpy(_msg + 4, _reply -> m_mcastIP, _reply -> m_mcastIPLen);
    _msg[4 + ipLen] = _reply -> m_mcastPortLen;
    memcpy(_msg + 4 + ipLen + 1, _reply -> m_mcastPort, _reply -> m_mcastPortLen);
    _msg[ipLen + portLen + 5] = '\0';
    return PROTOCOL_SUCCESS;
}


ProtocolStatus JoinGrpReplyUnpack (JoinGrpReply* _reply, const char* _msg)
{
    if (_reply == NULL || _msg == NULL)
    {
        return PROTOCOL_FAIL;
    }
    _reply -> m_requestStatus = _msg[2];
    _reply -> m_mcastIPLen = _msg[3];
    memcpy(_reply -> m_mcastIP, _msg + 4, (size_t)(_reply -> m_mcastIPLen));
    _reply -> m_mcastIP[ _reply -> m_mcastIPLen] = '\0';
    _reply -> m_mcastPortLen = _msg[4 + (size_t)(_reply -> m_mcastIPLen)];
    memcpy(_reply -> m_mcastPort, _msg + (5 + (size_t)(_reply -> m_mcastIPLen)), (size_t)(_reply -> m_mcastPortLen));
    _reply -> m_mcastPort[ _reply -> m_mcastPortLen] = '\0';
    return PROTOCOL_SUCCESS;
}

/*--LeaveGroup--*/
ProtocolStatus LeaveGrpRequestPack (const LeaveGrpRequest* _request, char* _msg);
ProtocolStatus LeaveGrpRequestUnpack (LeaveGrpRequest* _request, const char* _msg);
ProtocolStatus LeaveGrpReplyPack (const LeaveGrpReply* _reply, char* _msg);
ProtocolStatus LeaveGrpReplyUnpack (LeaveGrpReply* _reply, const char* _msg);

/*--LogOut--*/
ProtocolStatus LogOutRequestPack (const LogOutRequest* _request, char* _msg)
{
    if (_request == NULL || _msg == NULL)
    {
        return PROTOCOL_FAIL;
    }
    _msg[TAG] = LOG_OUT;
    _msg[LEN] = (strlen(_request -> m_username));
    strncpy(_msg + 2, _request -> m_username, strlen(_request -> m_username));
    return PROTOCOL_SUCCESS;
}

ProtocolStatus LogOutRequestUnpack (LogOutRequest* _request, const char* _msg)
{
    if (_request == NULL || _msg == NULL)
    {
        return PROTOCOL_FAIL;
    }
    strncpy(_request -> m_username, _msg + 2, (size_t)(_msg + 1));
    return PROTOCOL_SUCCESS;
}

ProtocolStatus LogOutReplyPack (const LogOutReply* _reply, char* _msg)
{
    if (_reply == NULL || _msg == NULL)
    {
        return PROTOCOL_FAIL;
    }
    _msg[TAG] = LOG_OUT;
    _msg[LEN] = '1';
    _msg[NAME_LEN] = _reply -> m_requestStatus;
    return PROTOCOL_SUCCESS;
}

ProtocolStatus LogOutReplyUnpack (LogOutReply* _reply, const char* _msg)
{
    if (_reply == NULL || _msg == NULL)
    {
        return PROTOCOL_FAIL;
    }
    _reply -> m_requestStatus = _msg[REQ_STS];
    return PROTOCOL_SUCCESS;
}