#ifndef USERINFO_H
#define USERINFO_H

bool isRoomAvailable(int roomNumber);
bool bookingIDExists(const char id[200]);

void makeRoomAvailiable();
void assignRoomToBookingID(const char id[200]);

#endif
