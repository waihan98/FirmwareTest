#include <stdint.h>
#include <stdio.h>

#define HIGH 1
#define LOW 0
#define ACTIVEHIGH 1
#define ACTIVELOW 0
#define NOINTERVAL 0

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
    uint16_t intervalStatus;            //interval level
    uint8_t state;                      //current state
}LEDstruct;

typedef struct  {
    uint8_t activeStatus;               //active high or low
    uint8_t lastState;                   //current state
    uint8_t triggerType;                 //Edge or Level trigger
    uint16_t debounce;                   //set debounce delay
    uint32_t lastPressTime;              //last pressed
    void (*callback)(void);
}PBStruct;

int set_led(enum LED led_number, uint16_t interval, uint8_t actStatus);
int set_push_button(enum PUSH_BUTTON push_button, void (*callback_func)(void));
void led_app(void);
void push_button_app(void);
void green_toggle(void);
void simulateButPress(enum PUSH_BUTTON push_button);


LEDstruct LED[2];
PBStruct  PB[2];
int main (void)
{
    set_push_button(PB_1,green_toggle);
    set_led(GREEN, NOINTERVAL, ACTIVEHIGH);
    set_led(RED, NOINTERVAL, ACTIVEHIGH);
    simulateButPress(PB_1);
    return 1;
}

int set_led(enum LED led_number, uint16_t interval, uint8_t actStatus)
{
    LED[led_number].intervalStatus = interval;
    LED[led_number].activeStatus = actStatus;
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
        if(LED[0].state == HIGH) printf("GREEN LED ON\n");
        else printf("GREEN LED OFF\n");
    }
    else
    {
        if(LED[0].state == LOW) printf("GREEN LED ON\n");
        else printf("GREEN LED OFF\n");
    }
}

void simulateButPress(enum PUSH_BUTTON push_button)
{
    if(PB[push_button].callback) PB[push_button].callback();
}