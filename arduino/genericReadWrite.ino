/*
  This sketch reads all analogue inputs and logs the valuea in JSON format to the serial line
  To compile and upload this sketch execute
  ./arduino-cli compile --fqbn arduino:avr:uno genericReadWrite.ino -o someName -u -p COM3
*/
/*
  The digital pins are named from 0 to 13 with 13 also beeing the built-in LED
  Digital pins 0 and 1 should be avoided as they are internally conneted to the serial line.
  The analogue pins A0 to A5 are named from 14 to 19
*/
String incomingMessage; // e.g. 0=1&2=0&3=1
String keyValue;        // splitted at &
String key;             // pin number 0...19
String value;           // status to set O for LOW and 1 for HIGH
long counter = 0L;      // count loops

// initialisation
void setup(){
  // init serial line with 115200 baud
  Serial.begin(115200);
  // init all digital pins
  for (int i = 0; i <= 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

// get status of all pin ans make JSON object
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

// main
void loop() {
  counter++;
  // ckeck if we have incoming message
  if (Serial.available() > 0) {
    incomingMessage = Serial.readString(); // Timeout is 1s
    bool repeat = true;
    while (repeat) {
      keyValue = "";
      int pos = incomingMessage.indexOf('&');
      if (pos > 0) {
        keyValue = incomingMessage.substring(0,pos);
        incomingMessage = incomingMessage.substring(pos+1);
      } else {
        keyValue = incomingMessage;
        repeat = false;
      }
      pos = keyValue.indexOf('=');
      if (pos > 0) {
        key = keyValue.substring(0,pos);
        value = keyValue.substring(pos+1);
        int pin = key.toInt();
        int state = value.toInt();
        if (pin >= 0 && pin <= 19 && ( state == 0 || state == 1 )) {
          // Serial.println("Setting input " + key + " to " + value);
          digitalWrite(pin, state);
        }
      }
    }
    // send IO status to host
    Serial.println(readPins());
  } else if (counter >= 1000000)  {
    // send IO status to host
    Serial.println(readPins());
    counter = 0L;
  } else {
    // do nothing
  }
} 