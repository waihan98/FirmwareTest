
#include <stdint.h>

typedef enum {
    IDLE = 0,
    RESERVED = 1,
    CHARGING = 2,
    ERROR = 3
}robotStatus;

typedef enum {
    AVAILABLE = 0,
    RESERVED = 1,
    CHARGING = 2,
    ERROR = 3
}stationStatus;

typedef struct 
{
    uint32_t        robotID;          //UID of Robot
    robotStatus     status;           //Status of Robot
    uint8_t         batLevel;         //Batt % level of Robot

}robot;

typedef struct
{
    uint32_t        stationID;          //UID of Station
    stationStatus   status;             //Status of Station
    uint32_t        reservedID;         //Reserved by Robot
}station;

