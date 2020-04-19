# Setup Visual Studio Code for Arduino on Windows

1. Download Arduino CLI from [arduino.github.io/arduino-cli](https://arduino.github.io/arduino-cli/installation)<br>
    Place this executable in a subfolder *arduino* of your project folder
2. Generate CLI config: ```./arduino-cli.exe config init```<br>
    This will create a config file and place it in *%AppData%/Local/Arduino15/arduino-cli.yaml*
3. Update board library: ```./arduino-cli core update-index```<br>
    This will download hardware information and store it in a file called *package_index.json* in the above mentioned directory
4. Show board info: ```./arduino-cli board list```<br>
    If the Arduino board is well connected via USB this will display the board information. The Arduino Uno board is referenced by **arduino:avr**
5. Install compiler for Arduino Uno: ```./arduino-cli core install arduino:avr```<br>
    This will install the corresponing compiler.
6. Compile sketch: ```./arduino-cli compile --fqbn arduino:avr:uno ./genericReadWrite.ino```<br>
    This will compile the sketch *genericReadWrite.ino* for Arduino Uno. Three files will be generated.
7.  Compile and upload in one step: ```./arduino/arduino-cli compile --fqbn arduino:avr:uno ./arduino/genericReadWrite.ino -o ./arduino/latest -u -p COM3```<br>
    In order to upload the firmware directly after compilation we have to add the option ```-u``` and specify the serial line to be used for upload ```-p COM3```. In order to avoid problem with the file names, we rename the output file to *latest* especially avoiding the extension *.ino* in the name.
8.  Configure the default build task (*Terminal > Configure Default Build Task...*) in Visual Studio Code so that **Ctrl+Shift+B** builds and uploads the firmware.

# Links
*  [Arduino CLI download and installation](https://arduino.github.io/arduino-cli/installation)
*  [Efficient Arduino Programming with Arduino CLI and Visual Studio Code](https://learn.sparkfun.com/tutorials/efficient-arduino-programming-with-arduino-cli-and-visual-studio-code/all)




