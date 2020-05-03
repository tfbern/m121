#include <Arduino.h>
#include "status.h"

// get status of all pin ans make JSON object, e.g. {"D0":1, ... , "A0":1023}
String readPins() {
  String ioStates = "{";
  for (int i = 0; i <= 19; i++) {
    ioStates += (i <= 13) ? "\"D" : "\"A";
    ioStates += (i <= 13) ? i : i-14;
    ioStates += "\":";
    ioStates += (i <= 13) ? digitalRead(i) : analogRead(i); 
    ioStates += (i == 19) ? "" : ",";
  }
  ioStates += "}";
  return ioStates;
}