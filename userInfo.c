#include "userInfo.h"

#include <string.h>

char      rooms_bookingId[6][256] = {};
bool      rooms_available[6] = {true, true, true, true, true, true};
BoardType rooms_boardType[6] = {};
int       rooms_numAdults[6] = {};
int       rooms_numChildldren[6] = {};
int       rooms_age[6] = {};


void checkoutRoom(const int roomNumber)
{
    rooms_available[roomNumber] = true;
}

void checkInRoom(const char id[256], const int roomNumber)
{
    rooms_available[roomNumber] = false;
    strcpy(bookingIDs[roomNumber], id);
}

bool isAnyRoomAvailable()
{
    for (int i = 0; i < 6; i++)
    {
        if (rooms_available[i]) return true;
    }

    return false;
}

bool isRoomAvailable(const int roomNumber)
{
    return rooms_available[roomNumber];
}

bool bookingIDExists(const char id[256])
{
    for(int i = 0; i < 6; i++)
    {
        if(strcmp(rooms_bookingId[i], id) != 0) return true;
    }

    return false;
}

BoardType getBoardType(const char id[256])
{

}
