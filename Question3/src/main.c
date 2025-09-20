#include <stdint.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

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
    uint8_t lastState;                      //current state
    uint8_t triggerType                 //Edge or Level trigger
    uint16_t debounce                   //set debounce delay
    uint32_t lastPressTime              //last pressed
}PBStruct;

int set_led(enum LED led_number, uint16_t interval);
int set_push_button(enum PUSH_BUTTON push_button, void (*callback_func)(void));
void led_app(void);
void push_button_app(void);

int main (void)
{
    uint8_t ledCol;
    uint8_t selDone = FALSE;
    while(selDone != TRUE)                  //Loop to make sure person select available color
    {
        printf("Select LED Colour \n");
        printf("Green [0]\t Red[1]\n");
        scanf("%hhu", &ledCol);
        if(ledCol >1)         //Ensure only 1 or 0
        {
            printf("Choose only 1 or 0\n");
        }
        else selDone = TRUE;
    }
    return 1;
}


