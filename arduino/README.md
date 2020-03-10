# Setup Visual Studio Code for Arduino

1. Generate CLI config: ```./arduino-cli.exe config init```
2. Update board library: ```./arduino-cli core update-index```
2. Show board info: ```./arduino-cli board list```
4. Install compiler for Arduino Uno: ```./arduino-cli core install arduino:avr```
5. Compile sketch: ```./arduino-cli compile --fqbn arduino:avr:uno .\genericReadWrite.ino```
6.  Compile and upload in one step: ```./arduino/arduino-cli compile --fqbn arduino:avr:uno ./arduino/genericReadWrite.ino -o ./arduino/latest -u -p COM3```

# Links
*  <a href="https://arduino.github.io/arduino-cli/installation/" target="_blank">Arduino CLI download and installation</a>
*  <a href="https://learn.sparkfun.com/tutorials/efficient-arduino-programming-with-arduino-cli-and-visual-studio-code/all" target="_blank">Efficient Arduino Programming with Arduino CLI and Visual Studio Code</a>




