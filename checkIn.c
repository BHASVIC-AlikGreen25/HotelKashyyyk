#include "checkIn.h"

#include <ctype.h>
#include <locale.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "userInfo.h"

bool isValidName(const char *name)
{
    if (name == nullptr || strlen(name) > 50)
    {
        // Validate name length not too long
        return false;
    }

    int wordCount = 0;
    int currentWordLength = 0;
    bool prevWasSpace = true;

    for (int i = 0; name[i] != '\0'; i++)
    {
        const char c = name[i];

        if (!isalpha(c) && c != ' ' && c != '-')
            return false; // If character is not alphanumeric or ' ' or '-' name is not valid

        if (c == ' ') // Handle spaces
        {
            if (prevWasSpace)
                return false;

            if (currentWordLength < 2)
                return false;  // Each word (first/surname) must be at least 2 characters

            wordCount++;
            currentWordLength = 0;
            prevWasSpace = true;
        }
        else // Handle all other characters
        {
            currentWordLength++;
            prevWasSpace = false;
        }
    }

    if (currentWordLength < 2) {
        return false;
    }

    wordCount++;

    // Must have at least 2 words
    return wordCount >= 2;
}

// Random function copied from the internet
typedef struct {
    uint64_t state;
    uint64_t inc;
} pcg32_random_t;


int random(const int min, const int max)
{
    return rand() % (max - min + 1) + min;
}

const char* generateBookingId(const char* name, char* bookingId)
{
    const char *surname = strrchr(name, ' ');
    const int num = random(0, 9999);

    snprintf(bookingId, 256, "%s-%04d", &surname[1], num);

    return bookingId;
}

int calculateAge(const int birthDay, const int birthMonth, const int birthYear)
{
    const time_t now = time(nullptr);
    const struct tm *currentTime = localtime(&now);

    const int currentDay = currentTime->tm_mday;
    const int currentMonth = currentTime->tm_mon + 1;  // tm_mon is 0-11
    const int currentYear = currentTime->tm_year + 1900;  // tm_year is years since 1900

    int age = currentYear - birthYear;

    if (currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay))
    {
        // If birthday hasn't happened yet this year subtract one
        age--;
    }
    return age;
}

bool isValidBirthday(const int birthDay, const int birthMonth, const int birthYear)
{
    if (birthDay < 0 ||
        birthMonth < 0 ||
        birthMonth > 12 ||
        birthYear < 1900) return false;

    const int age = calculateAge(birthDay, birthMonth, birthYear);

    if(age < 16 || age > 150) return false;

    return true;
}

void clearTerminal()
{
    for(int i = 0; i < 32; i++)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }
}

void printBar(const int length)
{
    for(int i = 0; i < length; i++)
        printf("-");

    printf("\n");
}

constexpr int roomPrices[6] = { 100, 100, 85, 75, 75, 50};

void displayRooms()
{
    printf("\n\n");


    printBar(88);
    printf("| Rooms        | Room 1    | Room 2    | Room 3    | Room 4    | Room 5    | Room 6    |\n");
    printf("---------------+-----------+-----------+-----------+-----------+-----------+------------\n");
    printf("| Availability |");
    for(int i = 0; i < 6; i++)
    {
        if(isRoomAvailable(i))
            printf(" AVAILABLE |");
        else
            printf(" OCCUPIED  |");
    }
    printf("\n");
    printf(  "---------------+-----------+-----------+-----------+-----------+-----------+------------\n");
    wprintf(L"| Price        | £100      | £100      | £85       | £75       | £75       | £50       |\n");
    printBar(88);

    printf("\n\n");
}

void checkIn()
{
    if(!isAnyRoomAvailable()) return;

    int success;

    char name[256];
    int birthDay, birthMonth, birthYear;
    int numAdults;
    int numChildren;
    int stayLength;
    int boardType = -1;
    bool dailyNewspaper = false;
    int roomNumber;
    char confirm;

    load();


    do
    {
        clearTerminal();

        printf("\n======== CHECK IN ========\n");

        printf("\nEnter your name (first and surname): ");
        fflush(stdin);
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
    }
    while (!isValidName(name));

    do
    {
        clearTerminal();
        printf("\n======== CHECK IN ========\n");
        printf("\nName: %s", name);

        printf("\nEnter your birth day (DD/MM/YYYY): ");
        fflush(stdin);
        success = scanf("%d/%d/%d", &birthDay, &birthMonth, &birthYear);

    }while (success != 3 || !isValidBirthday(birthDay, birthMonth, birthYear));

    do
    {
        clearTerminal();
        printf("\n======== CHECK IN ========\n");
        printf("\nName: %s", name);
        printf("\nDate of birth: %d/%d/%d", birthDay, birthMonth, birthYear);

        printf("\nInput number of adults 16 or over (1-4): ");
        fflush(stdin);
        success = scanf("%d", &numAdults);
    }while (success != 1 || numAdults < 1 || numAdults > 4);

    if(numAdults < 4)
    {
        do
        {
            clearTerminal();
            printf("\n======== CHECK IN ========\n");
            printf("\nName: %s", name);
            printf("\nDate of birth: %d/%d/%d", birthDay, birthMonth, birthYear);
            printf("\nNumber of adults: %d", numAdults);

            printf("\nInput number of children 15 or under (0-%d): ", 4-numAdults);
            fflush(stdin);
            success = scanf("%d", &numChildren);
        }while (success != 1 || numChildren < 0 || numChildren > 4-numAdults);
    }else
    {
        numChildren = 0;
    }

    do
    {
        clearTerminal();
        printf("\n======== CHECK IN ========\n");
        printf("\nName: %s", name);
        printf("\nDate of birth: %d/%d/%d", birthDay, birthMonth, birthYear);
        printf("\nNumber of adults: %d", numAdults);
        if(numChildren > 0) printf("\nNumber of children: %d", numChildren);

        printf("\nInput length of stay (days): ");
        fflush(stdin);
        success = scanf("%d", &stayLength);
    }while (success != 1 || stayLength < 1);

    do
    {
        clearTerminal();
        printf("\n======== CHECK IN ========\n");
        printf("\nName: %s", name);
        printf("\nDate of birth: %d/%d/%d", birthDay, birthMonth, birthYear);
        printf("\nNumber of adults: %d", numAdults);
        if(numChildren > 0) printf("\nNumber of children: %d", numChildren);
        printf("\nStay length: %d", stayLength);

        char boardTypeStr[16];

        printf("\n\nBoard types:");
        wprintf(L"\n    Full board [FB] - £20");
        wprintf(L"\n    Half board [HB] - £15");
        wprintf(L"\n    B&B        [BB] - £5");
        printf("\n\nInput type of board (FB, HB, BB): ");

        fflush(stdin);
        success = scanf("%s", &boardTypeStr);

        if(strlen(boardTypeStr) != 2 || tolower(boardTypeStr[1]) != 'b')
        {
            success = 0;
            continue;
        }

        if(tolower(boardTypeStr[0]) == 'f') boardType = 0;
        else if(tolower(boardTypeStr[0]) == 'h') boardType = 1;
        else if(tolower(boardTypeStr[0]) == 'b') boardType = 2;
    }while (success != 1 || boardType < 0);

    do
    {
        clearTerminal();
        printf("\n======== CHECK IN ========\n");
        printf("\nName: %s", name);
        printf("\nDate of birth: %d/%d/%d", birthDay, birthMonth, birthYear);
        printf("\nNumber of adults: %d", numAdults);
        if(numChildren > 0) printf("\nNumber of children: %d", numChildren);
        printf("\nStay length: %d", stayLength);

        const char* boardTypeFullName;
        if(boardType == 0) boardTypeFullName = "Full board";
        else if(boardType == 1) boardTypeFullName = "Half board";
        else boardTypeFullName = "Bed and breakfast";

        printf("\nBoard type: %s", boardTypeFullName);

        printf("\nWould you like a daily newspaper (Y/N): ");
        char dailyNewspaperChar;
        fflush(stdin);
        success = scanf("%c", &dailyNewspaperChar);
        if(tolower(dailyNewspaperChar) == 'y') dailyNewspaper = true;
        else if(tolower(dailyNewspaperChar) == 'n') dailyNewspaper = false;
        else success = 0;

    }while (success != 1);

    do
    {
        clearTerminal();
        printf("\n======== CHECK IN ========\n");
        printf("\nName: %s", name);
        printf("\nDate of birth: %d/%d/%d", birthDay, birthMonth, birthYear);
        printf("\nNumber of adults: %d", numAdults);
        if(numChildren > 0) printf("\nNumber of children: %d", numChildren);
        printf("\nStay length: %d", stayLength);

        const char* boardTypeFullName;
        if(boardType == 0) boardTypeFullName = "Full board";
        else if(boardType == 1) boardTypeFullName = "Half board";
        else boardTypeFullName = "Bed and breakfast";
        printf("\nBoard type: %s\n\n", boardTypeFullName);

        if(dailyNewspaper) printf("\nDaily newspaper: Yes");
        else printf("\nDaily newspaper: No");

        displayRooms();
        fflush(stdin);
        printf("Enter room number: ");
        success = scanf("%d", &roomNumber);
        roomNumber--;

    }while (!isRoomAvailable(roomNumber) || success != 1);

    do
    {
        clearTerminal();
        printf("\n======== CHECK IN ========\n");
        printf("\nName: %s", name);
        printf("\nDate of birth: %d/%d/%d", birthDay, birthMonth, birthYear);
        printf("\nNumber of adults: %d", numAdults);
        if(numChildren > 0) printf("\nNumber of children: %d", numChildren);
        printf("\nStay length: %d", stayLength);

        const char* boardTypeFullName;
        if(boardType == 0) boardTypeFullName = "Full board";
        else if(boardType == 1) boardTypeFullName = "Half board";
        else boardTypeFullName = "Bed and breakfast";
        printf("\nBoard type: %s", boardTypeFullName);

        if(dailyNewspaper) printf("\nDaily newspaper: Yes");
        else printf("\nDaily newspaper: No");

        printf("\nRoom number: %d", roomNumber+1);

        printf("\nWould you like to confirm the booking (Y/N): ");
        fflush(stdin);
        scanf("%c", &confirm);

        if(tolower(confirm) == 'n') return;

    }while (tolower(confirm) != 'y');

    char bookingId[256];
    generateBookingId(name, bookingId);

    const int age = calculateAge(birthDay, birthMonth, birthYear);
    checkInRoom(
        bookingId,
        roomNumber,
        boardType,
        stayLength,
        numAdults,
        numChildren,
        age,
        dailyNewspaper);

    save();

    printf("\nYour booking id: %s", bookingId);
    printf("\nMake sure to write it down.");
}
