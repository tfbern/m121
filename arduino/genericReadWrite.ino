/*
 * This sketch reads all analogue inputs and logs the valuea in JSON format to the serial line
 */
// A0 = 14
// A1 = 15
// A2 = 16
// A3 = 17
// A4 = 18
// A5 = 19
String incomingMessage = "";
String ioStates = "";
int t=1000; // Der Wert für „t“ gibt im Code die zeitlichen Abstände zwischen den einzelnen Messungen vor.

void setup(){
  Serial.begin(9600); //Im Setup beginnt die serielle Kommunikation, damit die Temperatur an den serial monitor übertragen wird. Über die serielle Kommunikation sendet das Board die Messwerte an den Computer. In der Arduino-Software kann man unter „Werkzeuge“ den „Seriellen Monitor“ starten um die Messwerte zu sehen.
  for (int i = 0; i <= 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  ioStates = "{";
  for (int i = 0; i <= 5; i++) {
    ioStates += "\"A";
    ioStates += i;
    ioStates += "\":";
    ioStates += analogRead(i+14); 
    if (i < 6) {
      ioStates += ",";
    }
  }
  
  for (int i = 0; i <= 13; i++) {
    ioStates += "\"D";
    ioStates += i;
    ioStates += "\":";
    ioStates += digitalRead(i); 
    if (i < 13) {
      ioStates += ",";
    }
  }
  ioStates += "}";
  Serial.println(ioStates);
  
  incomingMessage = Serial.readString(); // Timeout 1s
  if (incomingMessage.length() > 0) {
    Serial.println("Command: " + incomingMessage);
  }
  
  // delay(t);
}
