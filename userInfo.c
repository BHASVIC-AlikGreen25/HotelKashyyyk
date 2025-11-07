#include "userInfo.h"

#include <string.h>

bool      rooms_available[6] = {true, true, true, true, true, true};
char      rooms_bookingId[6][256] = {};
BoardType rooms_boardType[6] = {};
int       rooms_lengthStay[6] = {};
int       rooms_numAdults[6] = {};
int       rooms_numChildren[6] = {};
int       rooms_age[6] = {};
bool      rooms_dailyNewspaper[6] = {};


void checkoutRoom(const int roomNumber)
{
    rooms_available[roomNumber] = true;
}

void checkInRoom(const char id[256], const int roomNumber)
{
    if(!isRoomAvailable(roomNumber)) return;
    rooms_available[roomNumber] = false;
    strcpy(rooms_bookingId[roomNumber], id);
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
        if(strcmp(rooms_bookingId[i], id) == 0) return true;
    }

    return false;
}

int getRoomNumber(const char id[256])
{
    for(int i = 0; i < 6; i++)
    {
        if(strcmp(rooms_bookingId[i], id) != 0) return i;
    }

    return -1;
}

BoardType getBoardType(const char id[256])
{
    const int roomNumber = getRoomNumber(id);
    if(isRoomAvailable(roomNumber)) return FullBoard;

    return rooms_boardType[roomNumber];
}

int getStayLength(const char id[256])
{
    const int roomNumber = getRoomNumber(id);
    if(isRoomAvailable(roomNumber)) return -1;

    return rooms_lengthStay[roomNumber];
}

int getNumAdults(const char id[256])
{
    const int roomNumber = getRoomNumber(id);
    if(isRoomAvailable(roomNumber)) return -1;

    return rooms_numAdults[roomNumber];
}

int getNumChildren(const char id[256])
{
    const int roomNumber = getRoomNumber(id);
    if(isRoomAvailable(roomNumber)) return -1;

    return rooms_numChildren[roomNumber];
}

int getAge(const char id[256])
{
    const int roomNumber = getRoomNumber(id);
    if(isRoomAvailable(roomNumber)) return -1;

    return rooms_age[roomNumber];
}

bool hasDailyNewspaper(const char id[256])
{
    const int roomNumber = getRoomNumber(id);
    if(isRoomAvailable(roomNumber)) return false;

    return rooms_dailyNewspaper[roomNumber];
}

