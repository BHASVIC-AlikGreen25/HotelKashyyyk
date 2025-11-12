#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "checkIn.h"
#include "checkOut.h"
#include "dinnerTableBooking.h"

int main(void)
{
    setlocale(LC_ALL, "");
    setbuf(stdout, nullptr);
    srand(time(nullptr));

    checkIn();
    dinnerTableBooking();
    // checkOut();
    return 0;
}
