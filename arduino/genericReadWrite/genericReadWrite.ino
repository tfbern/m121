/*
  This sketch periodically reads all analog inputs and logs the values in JSON format to the serial line.
  In addition it will listen to the serial line and process any incoming messages.
  To compile and upload this sketch from the arduino folder execute 'arduino-cli compile genericReadWrite -u' 
  The options -b and -p will be taken automatically from sketch.json
  Upload is not possible while server.js is running because it uses the serial line also.

  The digital pins are named from 0 to 13. DIO 13 and the built-in LED are connected.
  Digital pins 0 and 1 should be avoided as they are internally conneted to the serial line.
  The analog pins A0 to A5 habe the IDs 14 to 19. 
  Hence, in order to query all IO states (digital and analog) we can make a loop from 0 to 19
*/

// global variables
unsigned long previousMillis = 0;   // count loops
const long interval = 1000;         // interval at which to send IO status updates (milliseconds)
bool avoidStringObjects = true;     // prefer c strings and functions insted of String objects

// initialisation
void setup(){
  // init serial line with 115200 baud
  Serial.begin(9600);
  // init all digital pins
  for (int i = 0; i <= 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

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

// get status of all pin ans make JSON object, e.g. {"D0":1, ... , "A0":1023}
// C version
char *readPinsC(char* out, int len) {
  strcat(out, "{");
  for (int i = 0; i <= 19; i++) {
    char type[2];
    strcpy(type, (i <= 13) ? "\"D" : "\"A");
    strcat(out, type);
    char sPort[2]; 
    int port = (i <= 13) ? i : i-14;
    itoa(port, sPort, 10);
    strcat(out, sPort);
    strcat(out, "\":");
    int value = (i <= 13) ? digitalRead(i) : analogRead(i);
    char sValue[5]; 
    itoa(value, sValue, 10);
    strcat(out, sValue);
    if (i != 19) strcat(out, ",");
  }
  strcat(out, "}");
  return out;
}

void processSerialInput() {
  String incomingMessage;                 // e.g. 0=1&2=0&3=1
  String keyValuePair;                    // splitted at &
  incomingMessage = Serial.readString();  // read the whole String in the serial buffer
  while (true) {
    // get the next key-value pair to process
    int pos = incomingMessage.indexOf('&');
    if (pos != -1) { 
      // '&' is present, we have multiple key-value pairs
      keyValuePair = incomingMessage.substring(0,pos); // get the first key-value pair
      processCommand(keyValuePair); // process it
      incomingMessage = incomingMessage.substring(pos+1); // and remove it from incomingMessage
    } else {
      // just one command or last command
      processCommand(incomingMessage); // process it
      break;
    }
  }
}

// process key-value pair 
void processCommand(String command) {
  int pos = command.indexOf('=');
  if (command.length() > 2 && pos > 0 ) { // min 3 characters with '=' present at minimum second position
    int pin = command.substring(0,pos).toInt(); // characters before '='
    int state = command.substring(pos+1).toInt(); // characters after '='
    if (pin >= 0 && pin <= 19 && ( state == 0 || state == 1 )) {
      // Serial.println("Setting input " + key + " to " + value);
      digitalWrite(pin, state);
    }
  }
}

// main
void loop() {
  // ckeck if we have incoming message, i.e. check if something is in the serial buffer
  if (Serial.available() > 0) {
    // receive messages on serial line, parse and handle the messages
    processSerialInput();
    // send updated IO status to host
    Serial.println(readPins());
  } else {
    // get the milliseconds since start
    unsigned long currentMillis = millis();
    // do only something if interval time has passed
    if (currentMillis - previousMillis >= interval)  { 
      // save the last time we sent the IO states
      previousMillis = currentMillis;
      // send IO states to host
      if (avoidStringObjects) {
        char states[14*7+6*10+2-1+1] = "";
        Serial.println(readPinsC(states, sizeof(states)-1)); // skip the \0 of the c string
      } else {
        Serial.println(readPins());
      }
      //

    } 
  }
} 