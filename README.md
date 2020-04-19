# Arduino IoT Tutorial
This is a tutorial to get started with Arduino Uno. We will measure the temparature and the luminance and display the results on a webpage. However, the implementation will be generic so that any analog and digital input can be read. As well all digital outputs can be changed.

## Development Environment Setup
1. Get an Arduino Kit. We are working with [learning set #8 from Funduino](https://www.funduinoshop.com/epages/78096195.sf/de_DE/?ObjectPath=/Shops/78096195/Products/01-U8)
1. Install Arduino IDE from [www.arduino.cc](https://www.arduino.cc/en/main/software).
    This is just for driver installation, we won't use this IDE it later as we use Visual Studio Code.
2. Install Visual Studio Code if you haven't already.
3. [Setup Visual Studio Code for Arduino](./arduino/README.md)

## Run the Project
1. Attach the sensors to Arduino
2. Open this project with Visual Studio Code
2. Compile the sketch *genericReadWrite.ino* and upload it to Arduino <br>
  After the setup above this can be achieved by the keyboard shortcut(**Ctrl+Shift+B**). This will run the shell command ```./arduino/arduino-cli compile --fqbn arduino:avr:uno ./arduino/genericReadWrite.ino -o ./arduino/latest -u -p COM3```
3. Start the server by running ```npm run start``` or ```nodemon ./server/server.js```
4. Open the GUI on [http://localhost](http://localhost)

## Links
* [www.arduino.cc](https://www.arduino.cc/)
* [www.funduino.de](https://funduino.de)
* [Lernset Nr.8 mit UNO Controller - Kit für Arduino](https://www.funduinoshop.com/epages/78096195.sf/de_DE/?ObjectPath=/Shops/78096195/Products/01-U8)
* [Temperatur messen](https://funduino.de/nr-9-temperatur-messen)
* [Fotowiderstand](https://funduino.de/nr-6-fotowiderstand)
* [Visual Studio Code](https://code.visualstudio.com/)
* [Arduino command line interface](https://github.com/arduino/arduino-cli)
* [Better Processing](https://vimeo.com/showcase/2801639/video/97524853)



