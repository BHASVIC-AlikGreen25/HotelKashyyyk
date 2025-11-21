#include "dinnerTableBooking.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "userInfo.h"

void ClearTerminal()
{
    for(int i = 0; i < 32; i++)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }
}

void dinnerTableBooking()
{
    char Table[99];
    bool Valid = false;
    int Time = 0;
    int AmountOfPeople = 0;
    bool Valid1 = false;
    char BookingID[256];

    ClearTerminal();
    do {
        printf("Please enter your BookingID: ");
        fflush(stdin);
        fgets(BookingID, sizeof(BookingID), stdin);
        if (!bookingIDExists(BookingID)) {
            printf("BookingID '%s' does not exist, please try again! \n", BookingID);
        }
        else {
            printf("BookingID found \n");
            Sleep(500);
        }
    } while (!bookingIDExists(BookingID));
    const char* Board = getBoardTypeAsString(BookingID);
    printf("Your current board type is: %s \n", Board);
    Sleep(500);
    if (strcmp(Board, "BB") == 0) {
        printf("Unfortunately as you are currently booked in for Bed and Breakfast, you are not eligible to book a table. \n");
    }
    else {
        do {
            printf("Please select a table from the following options: \n A) Endor(Seats 4 people) \n B) Naboo(Seats 4 people) \n C) Tatooine(Seats 4 people) \n");
            fflush(stdin);
            do {
                fgets(Table, 99, stdin);
                switch (tolower(Table[0])) {
                    case 'a':
                    case 'e':
                        strcpy(Table, "Endor");
                        Valid = true;
                        break;
                    case 'b':
                    case 'n':
                        strcpy(Table, "Naboo");
                        Valid = true;
                        break;
                    case'c':
                    case 't':
                        strcpy(Table, "Tatooine");
                        Valid = true;
                        break;
                    default:
                        printf("That is not a valid option! Try again. \n");
                        Valid = false;
                        break;
                }
            } while (Valid == false);
            printf("Please enter the time of your Booking: \n Enter 0 for 7PM \n Enter 1 for 9PM \n");
            fflush(stdin);
            scanf("%d", &Time);
            do {
                printf("How many people will be coming with you today? \n");
                fflush(stdin);
                scanf("%d", &AmountOfPeople);
                if (AmountOfPeople > 4) {
                    printf("Unfortunately you can only seat 4 people at the table. Please try again! \n");
                }
            } while (AmountOfPeople > 4);
            if (isTableBooked(Time, Table) == true) {
                printf("Unfortunately the table you selected is booked for that time. Please select another booking \n");
                Valid1 = false;
            }
            else {
                for (int i = 0; i < 5; i++) {
                    printf(".");
                    Sleep(300);
                }
                printf("\n");
                Valid1 = true;
                bookTable(Time, Table);
                printf("Your table has been booked successfully! \n");
                Sleep(500);
                printf("Booking view: \n");
                printf("=============================================================== \n");
                printf("Your BookingID: %s \n\n", BookingID);
                printf("Your Table: %s \n", Table);
                printf("Booking Time: ");
                if (Time == 0) {
                    printf("19:00 (7PM) \n");
                }
                else if (Time == 1) {
                    printf("21:00 (9PM) \n");
                }
                printf("Amount of People attending: %d", AmountOfPeople);
            }
        } while (Valid1 == false);
    }
}
