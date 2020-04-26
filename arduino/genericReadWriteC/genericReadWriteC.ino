/*
  This sketch periodically reads all analog inputs and logs the values in JSON format to the serial line.
  In addition it will listen to the serial line and process any incoming messages.
  To compile and upload this sketch from the arduino folder execute 'arduino-cli compile genericReadWriteC -u' 
  The options -b and -p will be taken automatically from sketch.json
  Upload is not possible while server.js is running because it uses the serial line also.

  The digital pins are named from 0 to 13. DIO 13 and the built-in LED are connected.
  Digital pins 0 and 1 should be avoided as they are internally conneted to the serial line.
  The analog pins A0 to A5 habe the IDs 14 to 19. 
  Hence, in order to query all IO states (digital and analog) we can make a loop from 0 to 19

  This version avoids the use of String object and uses C strings instead. 
  However, the implementation is not finished yet. There is still some use of String objects
  in processSerialInput() and processCommand()
*/

// global variables
unsigned long previousMillis = 0;   // count loops
const long interval = 1000;         // interval at which to send IO status updates (milliseconds)

// initialisation
void setup(){
  // init serial line with 9600 baud
  Serial.begin(9600);
  // init all digital pins
  for (int i = 0; i <= 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

// get status of all pin ans make JSON object, e.g. {"D0":1, ... , "A0":1023}
char *readPins(char* out, int len) {                        // *readPins means return the string content, not just the pointer
  strcat(out, "{");                                         // start JSON object with {
  for (int i = 0; i <= 19; i++) {                           // loop from 0 to 19
    char sType[3];                                          // string with max 2 char e.g. "D
    char sPort[3];                                          // string with max 2 char e.g. 1 or 14
    char sValue[5];                                         // string with max 4 char e.g. 0 or 1 or 1023
    strcpy(sType, (i <= 13) ? "\"D" : "\"A");               // copy literal "D or "A into string
    strcat(out, sType);                                     // add it to JSON object
    int port = (i <= 13) ? i : i-14;                        // get port number
    itoa(port, sPort, 10);                                  // convert int to string
    strcat(out, sPort);                                     // add it to JSON object
    strcat(out, "\":");                                     // add ": to JSON object
    int value = (i <= 13) ? digitalRead(i) : analogRead(i); // read value from digital/analog port
    itoa(value, sValue, 10);                                // convert value into string
    strcat(out, sValue);                                    // add it to JSON object
    if (i < 19) strcat(out, ",");                           // add , except last time
  }
  strcat(out, "}");                                         // close JSON object with }
  return out;                                               // return the JSON object as string
}

// process incoming messages
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
void processCommand(String &command) {  // &command makes receiving the String object by reference, hence avoid copies and save resources
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
  // max size of a JSON object is 14*6 (digital states) + 6*9 (analog states) + 19 (commas) + 2 (brackets) = 159
  char states[159+1] = "";  
  if (Serial.available() > 0) {
    // receive messages on serial line, parse and handle the messages
    processSerialInput();
    // send updated IO states to host
    Serial.println(readPins(states, sizeof(states)-1)); // skip the \0 of the c string
  } else {
    // get the milliseconds since start
    unsigned long currentMillis = millis();
    // do only something if interval time has passed
    if (currentMillis - previousMillis >= interval)  { 
      // save the last time we sent the IO states
      previousMillis = currentMillis;
      // send IO states to host
      Serial.println(readPins(states, sizeof(states)-1)); // skip the \0 of the c string
    } 
  }
} 