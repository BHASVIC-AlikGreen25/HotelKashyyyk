#include "checkOut.h"
#include <stdio.h>
#include "userInfo.h"


//float totalCostRoom=0;
//float totalCostFood=0;
//float roomCost=0;

//BoardType boardType=FullBoard;

//int age=0;
constexpr int k_pensioner=65;
constexpr int k_minor=16;
//int days=0;
//int guestsAdults=0;
//int guestsChildren=0;
//float foodCost=0;
//char id[256];




void userId(char *id,int *age,int *days,int *guestsAdults,int *guestsChildren) {

    do{
        wprintf(L"=========Welcome to Check Out=========\n\nPlease enter your ID: ");
        fflush(stdin);
        scanf("%s",id);

        if(bookingIDExists(id)==true)
        {
            *age=getAge(id);
            *days=getStayLength(id);
            *guestsAdults=getNumAdults(id);
            *guestsChildren=getNumChildren(id);
        }

    }while(bookingIDExists(id)==false);

}
float calculateFoodCost_Adults( int days, int guestsAdults, char *id) {
    float foodCostAdults=0;
    BoardType boardType=getBoardType(id);
    switch(boardType) {

        case FullBoard:
            foodCostAdults=days*guestsAdults*20;
        break;

        case HalfBoard:
            foodCostAdults=days*guestsAdults*15;
        break;

        case BnB:
            foodCostAdults=days*guestsAdults*5;
        break;

    }
    return foodCostAdults;
}
float calculateFoodCost_Children(BoardType boardType, int days, int guestsChildren){
    float foodCostChildren=0;
    switch(boardType) {
            case FullBoard:
                foodCostChildren=days*guestsChildren*20*0.5;
            break;

            case HalfBoard:
                foodCostChildren=days*guestsChildren*15*0.5;
            break;
            case BnB:
                foodCostChildren=days*guestsChildren*5*0.5;
            break;


    }
    return foodCostChildren;
}

    float calculateRoomCost(char *id, float roomCost, int days, int age) {
        int roomNumber=getRoomNumber(id)+1;
        switch(roomNumber) {
            case 1:
                case 2:
                roomCost=100*days;
            break;
            case 3:
                roomCost=85*days;
            break;
            case 4:
                case 5:
                roomCost=75*days;
            break;
            case 6:
                roomCost=50;
            break;
        }
        age=getAge(id);

    if(age>=k_pensioner) {
            roomCost=roomCost*0.9;
    }
    return roomCost;
}



float DailyNewspaperCost(char *id) {
    float newspaperCost=0;
    if(hasDailyNewspaper(id)==true) {
        newspaperCost+=5.50;

    }
    else {
        newspaperCost+=0;
    }
    return newspaperCost;
}

float g_grandTotal=0;

void billDisplay(float newspaperCost, float totalCostFood, float totalCostRoom){
    g_grandTotal=newspaperCost+totalCostRoom+totalCostFood;
    printf("=============Bill=============\n\n Grand Total: £%.2f\n",g_grandTotal);
    printf("Total food cost: £%.2f\n",totalCostFood);
    printf("Room cost: £%.2f\n",totalCostRoom);
    printf("Newspaper costs: £%.2f",newspaperCost);

}

void checkOut() {
    char id[256];
    int age=0;
    int days=0;
    int guestsAdults=0;
    int guestsChildren=0;
    float foodCost=0.0;
    BoardType boardType=getBoardType(id);
    float foodCostAdults=0.0;
    float foodCostChildren=0.0;
    float roomCost=0.0;
    float newspaperCost=0.0;
    float totalCostFood=0.0;
    float totalCostRoom=0.0;




    userId(id,&age,&days,&guestsAdults,&guestsChildren);
    foodCostAdults=calculateFoodCost_Adults(days,guestsAdults,id);
    foodCostChildren=calculateFoodCost_Children(boardType,days,guestsChildren);
    totalCostRoom=calculateRoomCost(id,roomCost,days,age);
    newspaperCost=DailyNewspaperCost(id);
    totalCostFood=foodCostAdults+foodCostChildren;
    billDisplay(newspaperCost,totalCostFood,totalCostRoom);
    int roomNumber=getRoomNumber(id);
    checkoutRoom(roomNumber);


}