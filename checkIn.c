#include "checkIn.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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



void checkIn()
{
    setbuf(stdout, nullptr);
    int success = 0;

    char name[256];
    int birthDay, birthMonth, birthYear;
    int numGuests;


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
        success = scanf("%d/%d/%d", &birthDay, &birthMonth, &birthYear);

    }while (success != 3 || !isValidBirthday(birthDay, birthMonth, birthYear));

    do
    {
        clearTerminal();
        printf("\n======== CHECK IN ========\n");
        printf("\nName: %s", name);
        printf("\nDate of birth: %d/%d/%d", birthDay, birthMonth, birthYear);

        printf("\nInput number of guests (1-4): ");
        success = scanf("%d", &numGuests);
    }while (success != 1 || numGuests < 1 || numGuests > 4);
}
