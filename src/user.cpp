#include "user.h"

#include <string.h>
#include <sstream>
#include <orbis/UserService.h>

int getLoggedInUser(User* user)
{
    int retValue = 0;
    int userID;
    char username[64];

    OrbisUserServiceInitializeParams param;
    param.priority = ORBIS_KERNEL_PRIO_FIFO_LOWEST;

    retValue = sceUserServiceInitialize(&param);
    if (retValue != 0) 
        return retValue;

    retValue = sceUserServiceGetInitialUser(&userID);
    if (retValue != 0)
        return retValue;

    (void)memset(username, 0, sizeof(username));

    retValue = sceUserServiceGetUserName(userID, username, sizeof(username) - 1);

    if (retValue == 0)
    {
        user->userID = userID;
        strcpy(user->username, username);
    }

    return retValue;
}