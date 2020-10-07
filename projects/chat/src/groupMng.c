#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "groupMng.h"
#include "queue.h"
#define MAX_LEN_USERNAME 16
#define MAX_IP 16
#define MAGIC_NUMBER 0xBEEFBEEF
#define DEAD_MAGIC_NUMBER 0xDEADBEEF
#define PORT 8080
#define LAST_HOST 50
#define FIRST_HOST 0
#define IP_LENGTH 16
#define FALSE 0
#define TRUE 1
#define QUEUE_SIZE 300
#define NETWORK_ADD "224.0.0."
#define CONTAINER_CAPACITY 10

struct Group
{
    int m_magic;
    size_t m_NumOfUser;
    int m_port;
	char m_groupName[MAX_LEN_USERNAME];
	char m_ip[IP_LENGTH];
};

struct GroupDB
{
    int m_magic;
    HashMap* m_container;
};

struct GroupMng
{
    size_t m_magic;
	GroupDB* m_Groups;
	Queue* m_IPpool;
};

/*================================================ static funcs =====================================*/

static char* GetIp(GroupMng* _manager);

static void GroupDBDestroy(GroupDB* _group);

GroupDB* GroupDBCreate();

static GroupSts GroupDBAddGroup(GroupDB* _groupDB, const char *_groupName ,Group* _group);

static size_t HashFunc(const void* _key);

static int EqualFunc(const void* _firstKey, const void* _secondKey);

static int KeyValueActionFunc(const void *_key, void *_value, void *_context);

static int InitIpPool(Queue* _ipPool);

/*===================================================================================================*/


GroupMng* GroupMngCreate()
{
	Queue* IPpool = NULL;
    GroupDB* groups = NULL;
    GroupMng* grp = (GroupMng *)malloc (sizeof(GroupMng));
    if (grp == NULL)
    {
        return NULL;
    }
    if(NULL == (IPpool = QueueCreate(QUEUE_SIZE)))
    {
        return NULL;
    }
    groups = GroupDBCreate();
    if (groups == NULL)
    {
        free(grp);
        return NULL;
    }
    grp -> m_magic = MAGIC_NUMBER;
    grp -> m_Groups = groups;
    grp -> m_IPpool = IPpool;
    InitIpPool(IPpool);

    CreateGroup(grp,"group1");
    CreateGroup(grp,"group2");
    CreateGroup(grp,"group3");
    CreateGroup(grp,"group4");
    return grp;
}

GroupDB* GroupDBCreate()
{
    HashMap* newHash;
    GroupDB *newGrp;
    if(NULL == (newHash = HashMapCreate(CONTAINER_CAPACITY, HashFunc, EqualFunc)))
	{
		return NULL;
	}
    if(NULL == (newGrp = (GroupDB *)malloc(sizeof(GroupDB))))
	{
		HashMapDestroy(&newHash, NULL, NULL);
		return NULL;
	}
    newGrp -> m_magic = MAGIC_NUMBER;
    newGrp -> m_container = newHash;
    return newGrp;
}

void GroupMngDestroy(GroupMng* _manager)
{
    if (_manager == NULL || _manager -> m_magic != MAGIC_NUMBER)
    {
        return;
    }
    _manager -> m_magic = DEAD_MAGIC_NUMBER;
    GroupDBDestroy(_manager -> m_Groups);
    free(_manager);
}

static void GroupDBDestroy(GroupDB* _group)
{
	if (NULL != _group && MAGIC_NUMBER == _group -> m_magic)
    {
        _group->m_magic = DEAD_MAGIC_NUMBER;
		HashMapDestroy(&_group-> m_container, NULL, NULL);
        free(_group);
    }
}




Group* CreateGroup(GroupMng* _manager, const char *_name)
{
    static int i = 1500;
    Group* newGrp = (Group*)malloc(sizeof(Group));
    char ip[MAX_IP];
    i++;
    if(newGrp == NULL || _name == NULL || _manager == NULL)
    {
        return NULL;
    }
    strncpy(ip ,GetIp(_manager), IP_LENGTH-1);
    newGrp -> m_NumOfUser = 0;
    newGrp -> m_port = PORT;
    strncpy(newGrp -> m_groupName, _name, MAX_LEN_USERNAME-1);
    strncpy(newGrp-> m_ip, ip, strlen(ip)); 
    printf("ip in group mng %s\n", ip);
    newGrp-> m_port = i;
    GroupDBAddGroup(_manager -> m_Groups, _name ,newGrp);
    newGrp -> m_magic = MAGIC_NUMBER;

    return newGrp;
}

static GroupSts GroupDBAddGroup(GroupDB* _groupDB, const char *_groupName ,Group* _group)
{
    if (_group == NULL || _group == NULL)
    {
        return GROUP_ERR;
    }
    if (MAP_SUCCESS != (HashMapInsert(_groupDB -> m_container, _groupName, _group)))
    {
		return GROUP_ERR;
	}
    return GROUP_OK;
}


void GetActiveGroups(GroupDB* _manager, const char *_fileName)
{
    size_t hashSize = HashMapSize(_manager->m_container);
    FILE* fp = fopen(_fileName, "w");

    if(NULL == fp)
    {
        return; /*TODO*/
    }
    fprintf(fp,"%s %s %s %s","group1", "group2", "group3", "group4");

}

static int KeyValueActionFunc(const void *_key, void *_value, void *_context)
{
    static size_t i = 0;
    printf("[%lu] %s \n",i++,(char*)_key);
    return TRUE;
}

static char* GetIp(GroupMng* _manager)
{
    char *val= (char*)malloc(sizeof(IP_LENGTH));
    QueueDequeue(_manager -> m_IPpool, (void**)&val);
    return val;
}

static int InitIpPool(Queue* _ipPool)
{
    char* ipAdd = NULL;
    size_t i = FIRST_HOST;
    void* res;
    Queue_Result ceck;
    char *val= (char*)malloc(sizeof(IP_LENGTH));
    while(i < LAST_HOST)
    {
        ipAdd = (char*)malloc(sizeof(IP_LENGTH));
        if(NULL == ipAdd)
        {
            return FALSE;
        }
        snprintf(ipAdd, IP_LENGTH, NETWORK_ADD "%lu", i++);
        if(QUEUE_SUCCESS != (ceck = QueueEnqueue(_ipPool, ipAdd)))
        {
            
        }
    }
    return TRUE;
}

char *GetGroupIp(const char* _groupName, GroupMng* _maneger)
{
    Group* tmp;
    if(_groupName == NULL || _maneger == NULL)
    {
        return NULL;
    }
    if((HashMapFind(_maneger -> m_Groups -> m_container, _groupName, (void**)&tmp)) == MAP_SUCCESS)
    {
        return tmp -> m_ip;
    }
    return NULL;
}

int GetGroupPort(const char* _groupName, GroupMng* _maneger)
{
    Group* tmp;
    if(_groupName == NULL || _maneger == NULL)
    {
        return GROUP_NULL;
    }
    if((HashMapFind(_maneger -> m_Groups -> m_container, _groupName, (void**)&tmp)) == MAP_SUCCESS)
    {
        return tmp -> m_port;
    }
    return 0;
}


GroupSts GroupDBAddUserToGroup(const char* _groupName, GroupMng* _maneger)
{
    Group* tmp;
    if(_groupName == NULL || _maneger == NULL)
    {
        return GROUP_NULL;
    }
    if((HashMapFind(_maneger -> m_Groups -> m_container, _groupName, (void**)&tmp)) == MAP_SUCCESS)
    {
        tmp -> m_NumOfUser++;
        return GROUP_OK;
    }
    return GROUP_ERR;

}



static size_t HashFunc(const void* _key)
{
	char username[MAX_LEN_USERNAME];
	size_t charsCounter;
	int i = 0;
	int counter = 0;
	strcpy(username, _key);
	for (; i < strlen(username);i++)
	{
		counter += (username[i] + '0');
	}
    return counter;
}


static int EqualFunc(const void* _firstKey, const void* _secondKey)
{

    if(!strcmp((const char*)_firstKey, (const char*)_secondKey))
	{
		return TRUE;
	}

	return FALSE;
}


