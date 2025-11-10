#include "dinnerTableBooking.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "userInfo.h"

void dinnerTableBooking()
{
    setbuf(stdout, NULL);
    char  tmpbuf[30];
    strcpy(tmpbuf,"KING-1101" );
    checkInRoom(tmpbuf, 3, FullBoard, 0, 0, 0, 0, 0); //Generate ID randomly later.
    char BookingID[256];
    char surname[999];
    do {
        printf("Please enter your BookingID: ");
        fflush(stdin);
        fgets(BookingID, sizeof(BookingID), stdin);
        //BookingID[strcspn(BookingID, "\n")] = 0; //Add to BookingIDExists function later
        if (!bookingIDExists(BookingID)) {
            printf("BookingID '%s' does not exist, please try again! \n", BookingID);
        }
        else {
            printf("BookingID found \n");
            sleep(1);
        }
    } while (!bookingIDExists(BookingID));
    const char* Board = getBoardTypeAsString(BookingID);
    printf("%s", Board);
}
