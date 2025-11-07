#include "dinnerTableBooking.h"
#include <stdio.h>
#include <string.h>

#include "userInfo.h"

void dinnerTableBooking()
{
    setbuf(stdout, NULL);
    checkInRoom("KING-1101", 3); //Generate ID randomly later.
    char BookingID[256];
    char surname[999];
    do {
        printf("Please enter your BookingID: ");
        fflush(stdin);
        fgets(BookingID, sizeof(BookingID), stdin);
        BookingID[strcspn(BookingID, "\n")] = 0; //Add to BookingIDExists function later
    } while (!bookingIDExists(BookingID));

}
