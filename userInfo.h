#pragma once

typedef enum {
    FullBoard,
    HalfBoard,
    BnB
} BoardType;

void checkoutRoom(int roomNumber);
void checkInRoom(const char id[256], int roomNumber);

bool isAnyRoomAvailable();
bool isRoomAvailable(int roomNumber);
bool bookingIDExists(char* id);

int getRoomNumber(char* id);

BoardType getBoardType(char* id);
const char* getBoardTypeAsString(char* id);
int getStayLength(char* id);
int getNumAdults(char* id);
int getNumChildren(char* id);
int getAge(char* id);
bool hasDailyNewspaper(char* id);