
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define HIGH 1
#define LOW 0
#define ACTIVEHIGH 1
#define ACTIVELOW 0
#define NOINTERVAL 0

#define PB1STATE 0       //testing button state
#define PB2STATE 1       //testing button state

enum LED{
    GREEN,
    RED,
};
enum PUSH_BUTTON{
    PB_1,
    PB_2,
};

typedef struct {
    uint8_t activeStatus;               //active high or low
    uint8_t state;                      //current state
    uint16_t intervalStatus;            //interval level
    uint64_t lastToggle;                //last toggled time
 
}LEDstruct;

typedef struct  {
    uint8_t activeStatus;               //active high or low
    uint8_t lastState;                   //current state
    uint8_t triggerType;                 //Edge or Level trigger
    uint32_t debounce;                   //set debounce delay
    uint64_t lastPressTime;              //last pressed
    void (*callback)(void);
}PBStruct;

int set_led(enum LED led_number, uint16_t interval, uint8_t actStatus);
int set_push_button(enum PUSH_BUTTON push_button, void (*callback_func)(void));
void led_app(void);
void push_button_app(void);
void green_toggle(void);
void change_blink_interval(void);
void simulateButPress(enum PUSH_BUTTON push_button);

uint64_t millisecond(void);
void clear_screen(void);
void sleep_ms(long milliseconds);


LEDstruct LED[2];
PBStruct  PB[2];

int main (void)
{
    set_push_button(PB_1,green_toggle);
    set_push_button(PB_2,change_blink_interval);
    set_led(GREEN, NOINTERVAL, ACTIVEHIGH);
    set_led(RED, NOINTERVAL, ACTIVEHIGH);
    
    while(1)
    {
        simulateButPress(PB_1);             //toggling pb1 to test
        led_app();
        push_button_app();
        clear_screen();
    }
    return 1;
}

int set_led(enum LED led_number, uint16_t interval, uint8_t actStatus)
{
    LED[led_number].intervalStatus = interval;
    LED[led_number].activeStatus = actStatus;
    LED[led_number].lastToggle = millisecond();
    return 1;
}

int set_push_button(enum PUSH_BUTTON push_button, void (*callback_func)(void))
{
    PB[push_button].callback = callback_func;
    return 1;
}
void green_toggle(void)
{
    LED[0].state ^= 1;       //toggle
    if(LED[0].activeStatus == ACTIVEHIGH)
    {
        printf("GREEN LED: %s\n", LED[GREEN].state ? "ON" : "OFF");
    }
    else
    {
        printf("GREEN LED: %s\n", LED[GREEN].state ? "OFF" : "ON");

    }
}

void change_blink_interval(void)
{
    if (LED[1].intervalStatus == 0)LED[1].intervalStatus = 500;
    else if (LED[1].intervalStatus == 500)LED[1].intervalStatus = 1000;
    else if (LED[1].intervalStatus == 1000)LED[1].intervalStatus = 2000;
    else LED[1].intervalStatus = 0;
}

void simulateButPress(enum PUSH_BUTTON push_button)
{
    if(PB[push_button].callback) PB[push_button].callback();
}

uint64_t millisecond(void)
{
    struct timeval time;
    gettimeofday(&time,NULL);
    return time.tv_sec * 1000 + time.tv_usec / 1000;
}

void led_app(void)
{   
    uint64_t curr = millisecond();
    if (LED[1].intervalStatus > 0)
    {
        if(curr - LED[1].lastToggle > LED[1].intervalStatus)
        {
            LED[1].state ^= 1;
            LED[1].lastToggle = curr;
        }
    }
    if(LED[1].activeStatus == ACTIVEHIGH)
    {
        if(LED[1].state == HIGH) printf("RED LED ON\n");
        else printf("RED LED OFF\n");
    }
    else
    {
        if(LED[1].state == LOW) printf("RED LED ON\n");
        else printf("RED LED OFF\n");
    }
}


void push_button_app(void)
{
    uint64_t curr = millisecond();
    if(PB1STATE != PB[0].lastState && (curr - PB[0].lastPressTime > PB[0].debounce)) //debounce for PB1
    {
        PB[0].lastState = PB1STATE;
        PB[0].lastPressTime = curr;
        PB[0].callback();
    }
    if(PB2STATE != PB[1].lastState && (curr - PB[1].lastPressTime > PB[1].debounce)) //debounce for PB2
    {
        PB[1].lastState = PB2STATE;
        PB[1].lastPressTime = curr;
        PB[1].callback();
    }
}

void clear_screen(void) {
    printf("\033[2J");   // Clear entire screen
    printf("\033[H");    // Move cursor to top-left
    fflush(stdout);      // Make sure it prints immediately
}
