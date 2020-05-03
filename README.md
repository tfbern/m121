# Arduino IoT Tutorial
This is a tutorial to get started with Arduino Uno. We will measure the temparature and the luminance and display the results on a webpage. However, the implementation will be generic so that any analog and digital input can be read. As well all digital outputs can be changed.

## Setup the Environment
1. Get an Arduino Kit. We are working with [learning set #8 from Funduino](https://www.funduinoshop.com/epages/78096195.sf/de_DE/?ObjectPath=/Shops/78096195/Products/01-U8)
2. Install Visual Studio Code if you haven't already.
3. Make sure Node.js and NPM are installed on your machine.
4. [Setup Visual Studio Code for Arduino](./arduino/README.md)

## Run the Project via Internet
In this setup the WebSocket sever will run on *websocksrv.herokuapp.com* and the webserver on *tfbern.github.io*.
1. Attach the temperature sensor TMP36 to analog input A0 (make attention to the polarization)
2. Attach Arduino Uno to the Computer via USB
3. Compile the sketch *genericReadWrite* and upload it to Arduino<br> ```arduino-cli compile arduino/genericReadWrite -u```
4. Run the serial-to-websocket gatway by running<br>
```nodemon``` in the folder *gateway*
5. Open the GUI from http://tfbern.github.io.samhess.ch/m121/index.html

## Run the Project Locally
In this setup the WebSocket sever will run on *localhost:81* and the webserver on *localhost*.
1. Attach the temperature sensor TMP36 to analog input A0 (make attention to the polarization)
2. Attach Arduino Uno to the Computer via USB
3. Compile the sketch *genericReadWrite* and upload it to Arduino <br>
  After [setting up Visual Studio Code for Arduino](./arduino/README.md) this can be achieved via the keyboard shortcut **Ctrl+Shift+B**. This will run the default build task which will execute the shell command ```arduino-cli compile arduino/genericReadWrite -u```
4. Start the server by running ```nodemon``` in the folder *server*.
5. Open the GUI on [http://localhost](http://localhost)

## Links
### Hardware Setup
* [www.funduino.de](https://funduino.de)
* [Lernset Nr.8 mit UNO Controller - Kit für Arduino](https://www.funduinoshop.com/epages/78096195.sf/de_DE/?ObjectPath=/Shops/78096195/Products/01-U8)
* [Temperatur messen](https://funduino.de/nr-9-temperatur-messen)
* [Fotowiderstand](https://funduino.de/nr-6-fotowiderstand)


### Tools
* [Visual Studio Code](https://code.visualstudio.com/)
* [Arduino command line interface](https://github.com/arduino/arduino-cli)
* [Git for Windows](https://gitforwindows.org)
* [TortoiseGit](https://tortoisegit.org/) 
* [Beyond Compare](https://www.scootersoftware.com/download.php)

### Sketch Programming
* [www.arduino.cc](https://www.arduino.cc/)
* [Sprach-Referenz](https://www.arduino.cc/reference/de/)
* [Built-In Examples](https://www.arduino.cc/en/Tutorial/BuiltInExamples)
* [Blink Without Delay](https://www.arduino.cc/en/tutorial/BlinkWithoutDelay)
* [Arduino Programming Cheat Sheet](https://github.com/liffiton/Arduino-Cheat-Sheet)
* [Arduino Befehlsübersicht](https://www.arduinoforum.de/code-referenz)
* [The Evils of Arduino Strings](https://hackingmajenkoblog.wordpress.com/2016/02/04/the-evils-of-arduino-strings/)
* [What is Heap Fragmentation?](https://cpp4arduino.com/2018/11/06/what-is-heap-fragmentation.html)
* [Dynamic Memory Allocation and Fragmentation in C and C++](https://www.design-reuse.com/articles/25090/dynamic-memory-allocation-fragmentation-c.html)
* [Speicher in Embedded Systems](http://dodo.fb06.fh-muenchen.de/hermann/esII/es2-vl123-v12.pdf)
* [AVR Libc](https://www.nongnu.org/avr-libc/)
* [C++ vs. The Arduino Language?](https://arduino.stackexchange.com/questions/816/c-vs-the-arduino-language)
* [How C Program Stored in RAM?](http://www.vishalchovatiya.com/how-c-program-stored-in-ram-memory/)

### Dependencies / Libraries
* [Simple to use, blazing fast and thoroughly tested WebSocket client and server for Node.js](https://github.com/websockets/ws)
* [Node SerialPort](https://serialport.io/)
* [Simple yet flexible JavaScript charting for designers & developers](https://www.chartjs.org/)
* [Express Schnelles, offenes, unkompliziertes Web-Framework für Node.js](https://expressjs.com/)


