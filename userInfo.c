#include "userInfo.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool      rooms_available[6] = {true, true, true, true, true, true};
char      rooms_bookingId[6][256] = { };
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

int getRoomNumber(char* id)
{
    normalizeID(id);
    for(int i = 0; i < 6; i++)
    {
        if(strcmp(rooms_bookingId[i], id) == 0) return i;
    }

    return -1;
}

bool bookingIDExists(char* id)
{
    normalizeID(id);
    for(int i = 0; i < 6; i++)
    {
        if(rooms_available[i]) continue;
        if(strcmp(rooms_bookingId[i], id) == 0) return true;
    }

    return false;
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
    if(table < 0 || table > 2 || time < 0 || time > 1) return;

    tables_available[time][table] = true;
}

bool isTableBooked(const int time, const int table)
{
    if(table < 0 || table > 2 || time < 0 || time > 1) return false;

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

const char* filePath = "../data.txt";

void save()
{
    FILE* file = fopen(filePath, "w");

    fprintf(file, "Available:\n");
    for (int i=0; i<6; ++i)
        fprintf(file, "%d\n", rooms_available[i]);

    fprintf(file, "Age:\n");
    for (int i=0; i<6; ++i)
        fprintf(file, "%d\n", rooms_age[i]);

    fprintf(file, "BoardType:\n");
    for (int i=0; i<6; ++i)
        fprintf(file, "%d\n", rooms_boardType[i]);

    fprintf(file, "DailyNewspaper:\n");
    for (int i=0; i<6; ++i)
        fprintf(file, "%d\n", rooms_dailyNewspaper[i]);

    fprintf(file, "LengthStay:\n");
    for (int i=0; i<6; ++i)
        fprintf(file, "%d\n", rooms_lengthStay[i]);

    fprintf(file, "Adults:\n");
    for (int i=0; i<6; ++i)
        fprintf(file, "%d\n", rooms_numAdults[i]);

    fprintf(file, "Children:\n");
    for (int i=0; i<6; ++i)
        fprintf(file, "%d\n", rooms_numChildren[i]);

    fprintf(file, "BookingIds:\n");
    for (int i=0; i<6; ++i)
    {
        if(rooms_bookingId[i][0] == 0)
            fputs("none\n", file);
        else
            fputs(rooms_bookingId[i], file);
    }

    fclose(file);
}

void load()
{
    FILE* file = fopen(filePath, "r");

    fscanf(file, "Available:\n");
    for (int i=0; i<6; ++i)
        fscanf(file, "%d\n", &rooms_available[i]);

    fscanf(file, "Age:\n");
    for (int i=0; i<6; ++i)
        fscanf(file, "%d\n", &rooms_age[i]);

    fscanf(file, "BoardType:\n");
    for (int i=0; i<6; ++i)
        fscanf(file, "%d\n", &rooms_boardType[i]);

    fscanf(file, "DailyNewspaper:\n");
    for (int i=0; i<6; ++i)
        fscanf(file, "%d\n", &rooms_dailyNewspaper[i]);

    fscanf(file, "LengthStay:\n");
    for (int i=0; i<6; ++i)
        fscanf(file, "%d\n", &rooms_lengthStay[i]);

    fscanf(file, "Adults:\n");
    for (int i=0; i<6; ++i)
        fscanf(file, "%d\n", &rooms_numAdults[i]);

    fscanf(file, "Children:\n");
    for (int i=0; i<6; ++i)
        fscanf(file, "%d\n", &rooms_numChildren[i]);

    fscanf(file, "BookingIds:\n");
    for (int i=0; i<6; ++i) {
        fgets(rooms_bookingId[i], 256, file);
        normalizeID(rooms_bookingId[i]);
    }


    fclose(file);
}

