#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "checkIn.h"
#include "checkOut.h"
#include "dinnerTableBooking.h"

void main()
{
    setlocale(LC_ALL, "");
    setbuf(stdout, nullptr);
    srand(time(nullptr));

    char choice = ' ';

    while(tolower(choice) != 'd')
    {
        printf("\n\nOptions:");
        printf("\n    A - Check-in user");
        printf("\n    B - Book a table for dinner");
        printf("\n    C - Checkout user");
        printf("\n    D - Exit program");
        printf("\nChoice: ");
        scanf("%c", &choice);

        switch(tolower(choice))
        {
            case 'a':
                checkIn();
                break;
            case 'b':
                dinnerTableBooking();
                break;
            case 'c':
                checkOut();
                break;
            default:
                break;
        }

        choice = ' ';
    }
}
