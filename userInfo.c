#include "userInfo.h"

#include <string.h>

char bookingIDs[6][256] = {0};
bool roomsAvailable[6] = {0};

void checkoutRoom(const int roomNumber)
{
    roomsAvailable[roomNumber] = true;
}

void checkInRoom(const char id[256], const int roomNumber)
{
    roomsAvailable[roomNumber] = false;
    strcpy(bookingIDs[roomNumber], id);
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
