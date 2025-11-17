#include "dinnerTableBooking.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "userInfo.h"

void dinnerTableBooking()
{
    char Table[99];
    bool Valid = false;

    setbuf(stdout, NULL);
    char  tmpbuf[30];
    strcpy( tmpbuf,"KING-1101" );
    checkInRoom( tmpbuf, 3, FullBoard, 0, 0, 0, 0, 0); //Generate ID randomly later.
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
    printf("Your current board type is: %s \n", Board);
    sleep(1);
    if (strcmp(Board, "BB") == 0) {
        printf("Unfortunately as you are currently booked in for Bed and Breakfast, you are not eligible to book a table. \n");
    }
    else {
        printf("Please select a table from the following options: \n A) Endor(Seats 4 people) \n B) Naboo(Seats 4 people) \n C) Tatooine(Seats 4 people) \n");
        do {
            printf("Input: ");
            fflush(stdin);
            fgets(Table, 99, stdin);
            fflush(stdin);
            if (strlen(Table) == 2) {
                switch (tolower(Table[0])) {
                    case 'a':
                        printf("...");
                        Valid = true;
                        break;
                    case 'b':
                        printf("..");
                        Valid = true;
                        break;
                    case 'c':
                        printf(".");
                        Valid = true;
                        break;
                    default:
                        printf("%s is not a valid table type, please try again! \n", Table);
                        break;
                }
            }
            else {
                printf("%s is not a valid table type, please try again! \n", Table);
                Valid = false;
            }
        } while (Valid == false);
    }
}
