#include "main.h"
#include "ModBusRTU.h"

u16u8_t registerFrame[200];

uint8_t gripperMovementStatus = 0, gripperMovementActualStatus = 0;
uint8_t zMovementStatus = 0;
double zPosition = 0, zSpeed = 0, zAccel = 0, zPoint = 0, xPosition = 0;
uint16_t pickOrder[6] = {0}, placeOrder[6] = {0};
double firstShelve = 0, secondShelve = 0, thirdShelve = 0, fourthShelve = 0, fifthShelve = 0;

