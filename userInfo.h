#pragma once

void checkoutRoom(int roomNumber);
void checkInRoom(const char id[256], int roomNumber);

bool isAnyRoomAvailable();
bool isRoomAvailable(int roomNumber);
bool bookingIDExists(const char id[200]);
