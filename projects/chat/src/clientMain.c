#include "../inc/clientManager.h"
#include "../inc/clientNetwork.h"
#include "../inc/chatProtocol.h"
#include "../inc/ChatProtocolLimits.h"
#include "../inc/userManager.h"
#include "../inc/userDB.h"
#include "../inc/ui.h"
#include "../inc/serverNetwork.h"
#include "../inc/serverManager.h"

int main()
{
    ClientMan* client = ClientManCreate();
    ClientManRun(client);
    return 0;
}