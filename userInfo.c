#include "userInfo.h"

#include <string.h>

char bookingIDs[6][256] = {};
bool roomsAvailable[6] = {true, true, true, true, true, true};

void checkoutRoom(const int roomNumber)
{
    roomsAvailable[roomNumber] = true;
}

void checkInRoom(const char id[256], const int roomNumber)
{
    roomsAvailable[roomNumber] = false;
    strcpy(bookingIDs[roomNumber], id);
}

bool isAnyRoomAvailable()
{
    for (int i = 0; i < 6; i++)
    {
        if (roomsAvailable[i]) return true;
    }

    return false;
}

bool isRoomAvailable(const int roomNumber)
{
    return roomsAvailable[roomNumber];
}

bool bookingIDExists(const char id[256])
{
    for(int i = 0; i < 6; i++)
    {
        if(strcmp(bookingIDs[i], id) != 0) return true;
    }

    return false;
}
