# Setup Visual Studio Code for Arduino on Windows
## Install the Arduino CLI and the Compiler
1. Download the latest version (currently 0.10.0) of Arduino CLI from 
    [arduino.github.io/arduino-cli](https://arduino.github.io/arduino-cli/installation)<br>
    Install this command line program in a folder that is part of your PATH system variable. Or, add the install directory to system PATH. Let's put it, where the global npm tools are located. There is a PowerShell Script *installArduinoCli.ps1* in the arduino folder.
2. Generate CLI config: 
    ```arduino-cli config init```<br>
    This will create a config file and place it in 
    *%AppData%/Local/Arduino15/arduino-cli.yaml*
3. Update board library: 
    ```arduino-cli core update-index```<br>
    This will download hardware information and store it in a file called *package_index.json* in the above mentioned directory
4. Install compiler for Arduino Uno: 
    ```arduino-cli core install arduino:avr```<br>
    This will install the corresponing compiler.

## Compile and Upload a Sketch
1. Clone this project and and open the folder in Visual Studio Code.
    Navigate to the folder *arduino*.
2. Check the content of the file *genericReadWrite/sketch.json* and if necessary 
    adjust the serial port with the values of ```arduino-cli board list```
3. Compile sketch by calling the compile command from outside the folder
    *genericReadWrite*:
    ```arduino-cli compile genericReadWrite```<br>
    This will compile the sketch *genericReadWrite*. Three files will be generated.
4.  Compile and upload in one step: 
    ```arduino-cli compile genericReadWrite -u```<br>
    In order to upload the firmware directly after compilation we have to add the option ```-u```.

## Use a Build Task and Auto Save
For more efficiency you can use a build task.
1.  Make sure the file *./.vscode/tasks.json* is present. If not, you would have to define a shell task that calls the above mentioned build command. 
    (*Terminal > Configure Tasks... > Create tasks.json from template > Others*)
2. You can now build and upload the **active** sketch (the currently open .ino file) by pressing **Ctrl+Shift+B** in Visual Studio Code.
3. Enable *Auto save* (*File > Auto Save*)

## genericReadWrite Sketch Versions
There are two versions genericReadWrite and genericReadWriteC in the arduino folder. Both sketches have the same functionality. The former is a C++ version and uses the String() Class of the Arduino Library. The latter is a C version and uses C string functions instead. However, the C implementation is not complete. There is still use of the String() Class. 

# Links
*  [Arduino CLI download and installation](https://arduino.github.io/arduino-cli/installation)
*  [Integrate with External Tools via Tasks](https://code.visualstudio.com/docs/editor/tasks#vscode)
*  [Efficient Arduino Programming with Arduino CLI and Visual Studio Code](https://learn.sparkfun.com/tutorials/efficient-arduino-programming-with-arduino-cli-and-visual-studio-code/all)




