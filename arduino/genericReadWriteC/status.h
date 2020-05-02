#include <Arduino.h>

// get status of all pin ans make JSON object, e.g. {"D0":1, ... , "A0":1023}
char * readPins(char *states);