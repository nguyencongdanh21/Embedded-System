//---------------------------------------------------[_INCLUDE LIBRARY_]-------------------------------------------------------//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include <wiringPi.h>
#include <softPwm.h>


//------------------------------------------------------[_DENFINE_]-----------------------------------------------------------//
#define LEDR  0   // pin 11
#define LEDG  1   // pin 12
#define LEDB  2   // pin 13
#define BT1   4   // pin 16
#define BT2   5   // pin 18

//---------------------------------------------------[_USER VARIABLE_]--------------------------------------------------------//
uint16_t duty=0;
uint8_t status=1;


//---------------------------------------------------[_USER FUNCTION_]--------------------------------------------------------//
void BT_interrupt(void)
{
    if(digitalRead(BT2)==1)
    {
        status= status+1;
        while(status%2==0)
        {
            digitalWrite(LEDR,HIGH);
        }
        while(status%2!=0)
        {
            digitalWrite(LEDR,LOW);
        }
    }
}

//---------------------------------------------------[_MAIN_PROGRAM_]---------------------------------------------------------//
int main()
{
    //-----------------------------------------------[CONFIRUGATION]---------------------------------------------------//
    wiringPiSetup();
    //----------------------------------------------[IO CONFIGURATION]-----------------------------------//
    //-----[BUTTON]----//
    pinMode(BT1,INPUT);
    pinMode(BT2,INPUT);

    //------[LED]------//
    pinMode(LEDR,OUTPUT);
    pinMode(LEDG,OUTPUT);
    pinMode(LEDB,OUTPUT);

    //-------[CREAT PWM]-------//
    softPwmCreate(LEDR,duty,100);
    softPwmCreate(LEDG,duty,100);
    softPwmCreate(LEDB,duty,100);

    //----------------------------------------------[INTERUPT CONFIGURATION]-----------------------------//
    wiringPiISR(BT1,INT_EDGE_RISING, &BT_interrupt);
    wiringPiISR(BT2,INT_EDGE_RISING, &BT_interrupt);

    //----------------------------------------------[WHILE_1 BEGIN]----------------------------------------------------//
    while(1)
    {

    }
    //----------------------------------------------[WHILE_1 END]------------------------------------------------------//

    return 0;
}

//---------------------------------------------------[__END__]----------------------------------------------------------------//
