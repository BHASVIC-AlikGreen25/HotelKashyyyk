#include "checkOut.h"
#include <stdio.h>
#include "userInfo.h"
#include "checkIn.c"

float g_totalCostRoom=0;
float g_totalCostFood=0;
float g_roomCost=0;

BoardType boardType=FullBoard;

int g_age=0;
const int g_pensioner=65;
const int g_minor=16;
int g_days=0;
int g_guestsAdults=0;
int g_guestsChildren=0;
float g_foodCost=0;
char g_id[256];


void userId() {
    printf("=========Welcome to Check Out=========\n\nPlease enter your ID: ");
    scanf("%s",&g_id);
}
void calculateFoodCost_Adults() {
    BoardType boardType=getBoardType(g_id);
    switch(boardType) {

        case FullBoard:
            g_foodCost=g_days*g_guestsAdults*20;
        break;

        case HalfBoard:
            g_foodCost=g_days*g_guestsAdults*15;
        break;

        case BnB:
            g_foodCost=g_days*g_guestsAdults*5;
        break;

    }
}
void calculateFoodCost_Children(){
        switch(boardType) {
            case FullBoard:
                g_foodCost+=g_days*g_guestsChildren*20*0.5;
            break;

            case HalfBoard:
                g_foodCost+=g_days*g_guestsChildren*15*0.5;
            break;
            case BnB:
                g_foodCost+=g_days*g_guestsChildren*5*0.5;
            break;

        }
}

    void calculateRoomCost() {
        int roomNumber=getRoomNumber(g_id)+1;
        switch(roomNumber) {
            case 1:
                case 2:
                g_roomCost=100*g_days;
            break;
            case 3:
                g_roomCost=85*g_days;
            break;
            case 4:
                case 5:
                g_roomCost=75*g_days;
            break;
            case 6:
                g_roomCost=50;
            break;

        }
        int age=getAge(g_id);

    if(age>=65) {
            g_roomCost=g_roomCost*0.9;
    }
}

float g_newspaperCost=0;

void DailyNewspaperCost() {
    if(hasDailyNewspaper(g_id)==true) {
        g_newspaperCost+=5.50;

    }
    else {
        g_newspaperCost+=0;
    }
}

float g_grandTotal=0;

void billDisplay(){
    g_grandTotal=g_newspaperCost+g_roomCost+g_foodCost;
    printf("=============Bill=============\n\n Grand Total: £%f");


}






