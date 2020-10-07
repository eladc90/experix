#include "userDB.h"


typedef struct GroupMng GroupMng;

typedef struct Group Group;

typedef struct GroupDB GroupDB;

typedef enum GroupSts
{
    GROUP_OK = 0,
    GROUP_ERR,
    GROUP_NULL

}GroupSts;

GroupMng* GroupMngCreate();

Group* CreateGroup(GroupMng* _manager, const char *_name);

void GetGroups(GroupMng* _manager);

void GroupMngDestroy(GroupMng* _manager);

GroupSts GroupMngAddUser(GroupMng* _groupMng, User* _user);

GroupSts GroupMngRemoveUser(GroupMng* _groupMng, User* _user);

void GetActiveGroups(GroupDB* _manager, const char *_fileName);

GroupSts GroupDBAddUserToGroup(const char* _groupName, GroupMng* _maneger);

char *GetGroupIp(const char* _groupName, GroupMng* _maneger);

int GetGroupPort(const char* _groupName, GroupMng* _maneger);



