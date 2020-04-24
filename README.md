# Arduino IoT Tutorial
This is a tutorial to get started with Arduino Uno. We will measure the temparature and the luminance and display the results on a webpage. However, the implementation will be generic so that any analog and digital input can be read. As well all digital outputs can be changed.

## Setup the Environment
1. Get an Arduino Kit. We are working with [learning set #8 from Funduino](https://www.funduinoshop.com/epages/78096195.sf/de_DE/?ObjectPath=/Shops/78096195/Products/01-U8)
2. Install Visual Studio Code if you haven't already.
3. [Setup Visual Studio Code for Arduino](./arduino/README.md)

## Run the Project
1. Attach Arduino Uno to the Computer via USB
    * Attach the temperature sensor TMP36 to analog input A0 (make attention to the polarization)
2. Open this project with Visual Studio Code (File > Open Folder...)
2. Compile the sketch *genericReadWrite.ino* and upload it to Arduino <br>
  After [setting up Visual Studio Code for Arduino](./arduino/README.md) this can be achieved via the keyboard shortcut **Ctrl+Shift+B**. This will run the default build task which will execute the shell command ```arduino-cli compile arduino/genericReadWrite -u```
3. Start the server by running ```npm run start``` or ```nodemon ./server/server.js```
4. Open the GUI on [http://localhost](http://localhost)

## Links
* [www.arduino.cc](https://www.arduino.cc/)
    * [Sprach-Referenz](https://www.arduino.cc/reference/de/)
* [www.funduino.de](https://funduino.de)
    * [Lernset Nr.8 mit UNO Controller - Kit für Arduino](https://www.funduinoshop.com/epages/78096195.sf/de_DE/?ObjectPath=/Shops/78096195/Products/01-U8)
    * [Temperatur messen](https://funduino.de/nr-9-temperatur-messen)
    * [Fotowiderstand](https://funduino.de/nr-6-fotowiderstand)
* [Visual Studio Code](https://code.visualstudio.com/)
* [Arduino command line interface](https://github.com/arduino/arduino-cli)
* [Arduino Programming Cheat Sheet](https://github.com/liffiton/Arduino-Cheat-Sheet)
* [Arduino Befehlsübersicht](https://www.arduinoforum.de/code-referenz)
* [Better Processing](https://vimeo.com/showcase/2801639/video/97524853)


<!--
2. Install Arduino IDE from [www.arduino.cc](https://www.arduino.cc/en/main/software).
    This is just for driver installation, we won't use this IDE it later as we use Visual Studio Code.
-->



