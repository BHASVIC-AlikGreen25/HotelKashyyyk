#include "userInfo.h"

#include <ctype.h>
#include <string.h>

bool      rooms_available[6] = {true, true, true, true, true, true};
char      rooms_bookingId[6][256] = {};
BoardType rooms_boardType[6] = {};
int       rooms_lengthStay[6] = {};
int       rooms_numAdults[6] = {};
int       rooms_numChildren[6] = {};
int       rooms_age[6] = {};
bool      rooms_dailyNewspaper[6] = {};

bool tables_available[2][3] = {};

void normalizeID(char *id)
{
    id[strcspn(id, "\n")] = 0;

    for(int i = 0; id[i]; i++)
    {
        id[i] = tolower(id[i]);
    }
}

void checkoutRoom(const int roomNumber)
{
    rooms_available[roomNumber] = true;
}

// This changes id string
void checkInRoom(char* id,
                 const int roomNumber,
                 const BoardType board,
                 const int stayLength,
                 const int adults,
                 const int children,
                 const int age,
                 const bool dailyNewspaper)
{
    normalizeID(id);
    if(!isRoomAvailable(roomNumber)) return;

    rooms_available[roomNumber] = false;
    strcpy(rooms_bookingId[roomNumber], id);
    rooms_boardType[roomNumber] = board;
    rooms_lengthStay[roomNumber] = stayLength;
    rooms_numAdults[roomNumber] = adults;
    rooms_numChildren[roomNumber] = children;
    rooms_age[roomNumber] = age;
    rooms_dailyNewspaper[roomNumber] = dailyNewspaper;
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

bool bookingIDExists(char* id)
{
    normalizeID(id);
    for(int i = 0; i < 6; i++)
    {
        if(strcmp(rooms_bookingId[i], id) == 0) return true;
    }

    return false;
}

int getRoomNumber(char* id)
{
    normalizeID(id);
    for(int i = 0; i < 6; i++)
    {
        if(strcmp(rooms_bookingId[i], id) == 0) return i;
    }

    return -1;
}

BoardType getBoardType(char* id)
{
    normalizeID(id);
    const int roomNumber = getRoomNumber(id);
    if(isRoomAvailable(roomNumber)) return FullBoard;

    return rooms_boardType[roomNumber];
}

const char * getBoardTypeAsString(char* id)
{
    normalizeID(id);
    const BoardType board = getBoardType(id);

    switch (board) {
        case FullBoard:
            return "FB";
        case HalfBoard:
            return "HB";
        case BnB:
            return "BB";
    }

    return "";
}

int getStayLength(char* id)
{
    normalizeID(id);
    const int roomNumber = getRoomNumber(id);
    if(isRoomAvailable(roomNumber)) return -1;

    return rooms_lengthStay[roomNumber];
}

int getNumAdults(char* id)
{
    normalizeID(id);
    const int roomNumber = getRoomNumber(id);
    if(isRoomAvailable(roomNumber)) return -1;

    return rooms_numAdults[roomNumber];
}

int getNumChildren(char* id)
{
    normalizeID(id);
    const int roomNumber = getRoomNumber(id);
    if(isRoomAvailable(roomNumber)) return -1;

    return rooms_numChildren[roomNumber];
}

int getAge(char* id)
{
    normalizeID(id);
    const int roomNumber = getRoomNumber(id);
    if(isRoomAvailable(roomNumber)) return -1;

    return rooms_age[roomNumber];
}

bool hasDailyNewspaper(char* id)
{
    normalizeID(id);
    const int roomNumber = getRoomNumber(id);
    if(isRoomAvailable(roomNumber)) return false;

    return rooms_dailyNewspaper[roomNumber];
}


// Time should be 0 for 7pm booking or 1 for 9 pm booking
// Table should be between 0 and 3 for the 3 tables
void bookTable(const int time, const int table)
{
    if(table < 0 || table > 3 || time < 0 || time > 1) return;

    tables_available[time][table] = true;
}

bool isTableBooked(const int time, const int table)
{
    if(table < 0 || table > 3 || time < 0 || time > 1) return false;

    return tables_available[time][table];
}

bool isAnyTableAvailable()
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(tables_available[i][j]) return true;
        }
    }

    return false;
}

