/*
 * Name: Nathan Culler
 * Date: 7/31/2023
 * Assignment: Lab 4
 * YouTube: https://youtu.be/L-fUqsBaMnI
 *
 * This Program:
 * will use an ultrasonic sensor to measure distance and activate a buzzer.
 */
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {IDLE, ARMED, ALARM} state_t;

void init();
void initClock();
void initTimer();
void SetBuzzer(bool state);
bool ButtonOnePressed();
bool ButtonTwoPressed();
void SetRedLED(bool state);
void SetGreenLED(bool state);
float getDistance();
state_t RunIdleState(bool isS1Pressed);
state_t RunArmedState(bool isS1Pressed);
state_t RunAlarmState(bool isS1Pressed);

int main(void)
{
    state_t currentState = IDLE;
    state_t nextState = currentState;
    bool isS1Pressed = false;

    init();
    //initClock();

    while(1){
        switch(currentState){
        case IDLE:
            nextState = RunIdleState(isS1Pressed);
            break;
        case ARMED:
            nextState = RunArmedState(isS1Pressed);
            break;
        case ALARM:
            nextState = RunAlarmState(isS1Pressed);
            break;
        default:
            SetRedLED(true);
            SetGreenLED(true);
            break;
        }
        isS1Pressed = ButtonOnePressed();
        __delay_cycles(100000);
        currentState = nextState;

    }

	return 0;
}

void init(){
    // ultrasonic sensor is P6.2
    // buzzer is P5.4
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P4DIR &= ~BIT1; //Button 1
    P4REN |= BIT1;
    P4OUT |= BIT1;
    P2DIR &= ~BIT3; //Button 2
    P2REN |= BIT3;
    P2OUT |= BIT3;
    P5DIR |= BIT4; //Buzzer
    P5OUT &= ~BIT4;
    P6OUT &= ~BIT2;
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    P6DIR |= BIT6;
    P6OUT &= ~BIT6;
}

void SetBuzzer(bool state){
    if(state){
        P5OUT |= BIT4;
    }
    else {
        P5OUT &= ~BIT4;
    }
}

bool ButtonOnePressed(){
    if((P4IN & BIT1) == 0X00){
        while((P4IN & BIT1) == 0X00);
        return true;
    }
    else {
        return false;
    }
}

void SetRedLED(bool state){
    if(state){
        P1OUT |= BIT0;
    }
    else {
        P1OUT &= ~BIT0;
    }
}

void SetGreenLED(bool state){
    if(state){
        P6OUT |= BIT6;
    }
    else {
        P6OUT &= ~BIT6;
    }
}

float getDistance(){
   volatile float countValue = 0;
   volatile float distance = 0;
   TB0R = 0;

    P6DIR |= BIT2; //pin 2 set to output trigger
    P6OUT &= ~BIT2;
    __delay_cycles(10); //10 microsecond delay
    P6OUT |= BIT2; //pin 2 output high
    __delay_cycles(10); //10 microsecond delay
    P6OUT &= ~BIT2;

    P6DIR &= ~BIT2; //configure as input

    //wait for signal to go high
    while((P6IN & BIT2) == 0X00);
    //start timer
    TB0CTL = TBSSEL__SMCLK | MC__CONTINUOUS;
    //wait for signal to go low
    while((P6IN & BIT2));
    //stop timer
    TB0CTL = TBSSEL__SMCLK | MC__STOP;
    countValue = TB0R;

    distance = (343.0 * countValue * (1.0/(1000000.0)))/2.0; //meters
    return distance;
}

state_t RunIdleState(bool isS1Pressed){
    state_t nextState;

    SetGreenLED(false);
    SetRedLED(false);
    SetBuzzer(false);
    if(isS1Pressed){
        nextState = ARMED;
    }
    return nextState;
}
state_t RunArmedState(bool isS1Pressed){

    state_t nextState;

    volatile static float previousDistance;
    volatile float currentDistance = 0.0;
    volatile static uint32_t count = 0.0;

    volatile float trip = 0.0;

    SetBuzzer(false);
    SetGreenLED(true);
    SetRedLED(false);

    currentDistance = getDistance();


    if(count > 0){
        trip = previousDistance - getDistance();
        if(trip > 0.2){
            nextState = ALARM;
            count = 0.0;
        }
        else{
            nextState = ARMED;
        }
    }
    else{
        nextState = ARMED;
    }
    previousDistance = currentDistance;
    count++;
    return nextState;
}
state_t RunAlarmState(bool isS1Pressed){
    state_t nextState;

    SetGreenLED(false);
    SetRedLED(true);
    SetBuzzer(true);
    if(isS1Pressed){
        nextState = IDLE;
    }
    else {
        nextState = ALARM;
    }
    return nextState;
}
