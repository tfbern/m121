#include <Arduino.h>
#include "status.h"

// get status of all pin ans make JSON object, e.g. {"D0":1, ... , "A0":1023}
char * readPins(char *states) {                        // *readPins means return the string content, not just the pointer
  // max size of a JSON object is 14*6 (digital states) + 6*9 (analog states) + 19 (commas) + 2 (brackets) = 159 
  strcat(states, "{");                                      // start JSON object with {
  for (int i = 0; i <= 19; i++) {                           // loop from 0 to 19
    char sType[3];                                          // string with max 2 char e.g. "D
    char sPort[3];                                          // string with max 2 char e.g. 1 or 14
    char sValue[5];                                         // string with max 4 char e.g. 0 or 1 or 1023
    strcpy(sType, (i <= 13) ? "\"D" : "\"A");               // copy literal "D or "A into string
    strcat(states, sType);                                  // add it to JSON object
    int port = (i <= 13) ? i : i-14;                        // get port number
    itoa(port, sPort, 10);                                  // convert int to string
    strcat(states, sPort);                                  // add it to JSON object
    strcat(states, "\":");                                  // add ": to JSON object
    int value = (i <= 13) ? digitalRead(i) : analogRead(i); // read value from digital/analog port
    itoa(value, sValue, 10);                                // convert value into string
    strcat(states, sValue);                                 // add it to JSON object
    if (i < 19) strcat(states, ",");                           // add , except last time
  }
  strcat(states, "}");                                         // close JSON object with }
  return states;                                               // return the JSON object as string
}