#include "userInfo.h"

#include <string.h>

char bookingIDs[6][256] = {0};

bool isRoomAvailable(int roomNumber)
{
    return bookingIDs[roomNumber] == nullptr;
}

bool bookingIDExists(const char id[256])
{
    for(int i = 0; i < 6; i++)
    {
        if(strcmp(bookingIDs[i], id)) return true;
    }

    return false;
}
