#include "checkIn.h"

#include <ctype.h>
#include <locale.h>
#include <stdio.h>
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

        if (!isalnum(c) && c != ' ' && c != '-')
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

bool isValidBirthday(const int birthDay, const int birthMonth, const int birthYear)
{
    if (birthDay < 0 ||
        birthMonth < 0 ||
        birthMonth > 12 ||
        birthYear < 1900) return false;

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

    if(age < 18 || age > 150) return false;

    return true;
}

void clearTerminal()
{
    for(int i = 0; i < 32; i++)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }
}

void displayRooms()
{
    printf("\n======== ROOM AVAILABILITY ========\n\n");

    for(int i = 0; i < 6; i++) {
        printf("  Room %d: ", 1 + i);

        if(isRoomAvailable(i)) {
            printf("[  AVAILABLE  ]\n");
        } else {
            printf("[   OCCUPIED  ]\n");
        }
    }

    printf("\n==================================\n");
}

void checkIn()
{
    setlocale(LC_ALL, "");
    setbuf(stdout, nullptr);

    if(!isAnyRoomAvailable()) return;

    int success = 0;

    char name[256];
    int birthDay, birthMonth, birthYear;
    int numAdults;
    int numChildren;
    int stayLength;
    int boardType = -1;
    bool dailyNewspaper;


    do
    {
        clearTerminal();
        displayRooms();

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
        success = scanf("%d/%d/%d", &birthDay, &birthMonth, &birthYear);

    }while (success != 3 || !isValidBirthday(birthDay, birthMonth, birthYear));

    do
    {
        clearTerminal();
        printf("\n======== CHECK IN ========\n");
        printf("\nName: %s", name);
        printf("\nDate of birth: %d/%d/%d", birthDay, birthMonth, birthYear);

        printf("\nInput number of adults (1-4): ");
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

            printf("\nInput number of children (0-%d): ", 4-numAdults);
            success = scanf("%d", &numChildren);
        }while (success != 1 || numChildren < 1 || numChildren > 4-numAdults);
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

        if(strlen(boardTypeStr) != 2)
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

        const char* boardTypeFullName = "";
        if(boardType == 0) boardTypeFullName = "Full board";
        else if(boardType == 1) boardTypeFullName = "Half board";
        else if(boardType == 2) boardTypeFullName = "Bed and breakfast";

        printf("\nBoard type: %s", boardTypeFullName);

        printf("\nWould you like a daily newspaper (Y/N): ");
        char dailyNewspaperChar;
        success = scanf("%c", &dailyNewspaperChar);
        if(tolower(dailyNewspaperChar) == 'y') dailyNewspaper = true;
        else if(tolower(dailyNewspaperChar) == 'n') dailyNewspaper = false;
        else success = 0;

    }while (success != 1 || numAdults < 1 || numAdults > 4);

    do
    {
        clearTerminal();
        printf("\n======== CHECK IN ========\n");
        printf("\nName: %s", name);
        printf("\nDate of birth: %d/%d/%d", birthDay, birthMonth, birthYear);
        printf("\nNumber of adults: %d", numAdults);
        if(numChildren > 0) printf("\nNumber of children: %d", numChildren);
        printf("\nStay length: %d", stayLength);

        const char* boardTypeFullName = "";
        if(boardType == 0) boardTypeFullName = "Full board";
        else if(boardType == 1) boardTypeFullName = "Half board";
        else if(boardType == 2) boardTypeFullName = "Bed and breakfast";

        printf("\nBoard type: %s\n\n", boardTypeFullName);

        displayRooms();



    }while (numAdults < 1 || numAdults > 4);
}
