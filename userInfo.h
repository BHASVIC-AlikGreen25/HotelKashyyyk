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
bool bookingIDExists(const char id[256]);

int getRoomNumber(const char id[256]);

BoardType getBoardType(const char id[256]);
int getStayLength(const char id[256]);
int getNumAdults(const char id[256]);
int getNumChildren(const char id[256]);
int getAge(const char id[256]);