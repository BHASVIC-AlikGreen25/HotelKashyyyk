cmake_minimum_required(VERSION 3.28)
project(HotelKashyyyk C)

set(CMAKE_C_STANDARD 23)

add_executable(HotelKashyyyk main.c
        checkIn.h
        checkIn.c
        dinnerTableBooking.h
        dinnerTableBooking.c
        checkOut.h
        checkOut.c
        userInfo.h)
