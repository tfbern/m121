# Setup Visual Studio Code for Arduino on Windows



1. Download the latest version (currently 0.10.0) of Arduino CLI from [arduino.github.io/arduino-cli](https://arduino.github.io/arduino-cli/installation)<br>
    Install this command line program in a folder that is part of your PATH environment variable. Let's put it, where the global npm tools are located. Here the PowerShell commands for the installation:

        $url = 'https://github.com/arduino/arduino-cli/releases/download/0.10.0/arduino-cli_0.10.0_Windows_64bit.zip'
        $tmp = 'arduino-cli.zip'
        Invoke-WebRequest $url -OutFile $tmp
        Expand-Archive -Path $tmp -DestinationPath  $($env:APPDATA + '\npm')
        $tmp | Remove-Item

2. Generate CLI config: 
    ```arduino-cli config init```<br>
    This will create a config file and place it in *%AppData%/Local/Arduino15/arduino-cli.yaml*
3. Update board library: 
    ```arduino-cli core update-index```<br>
    This will download hardware information and store it in a file called *package_index.json* in the above mentioned directory
4. Show board info: 
    ```arduino-cli board list```<br>
    If the Arduino board is well connected via USB this will display the board information. The Arduino Uno board is referenced by **arduino:avr**
5. Install compiler for Arduino Uno: 
    ```arduino-cli core install arduino:avr```<br>
    This will install the corresponing compiler.
6. Check the content of the file *sketch.json* and adjust it with the values gained unter point 4.
7. Compile sketch:
    ```arduino-cli compile genericReadWrite```<br>
    This will compile the sketch *genericReadWrite.ino* within the folder *genericReadWrite*. Three files will be generated.
8.  Compile and upload in one step: 
    ```arduino-cli compile genericReadWrite -u```<br>
    In order to upload the firmware directly after compilation we have to add the option ```-u```.
9.  Make sure the file *./.vstudio/tasks.json* is present. If not, you would have to define a shell task that calls the above mentioned build command. (*Terminal > Configure Tasks... > Create tasks.json from template > Others*)
10.  Configure the default build task (*Terminal > Configure Default Build Task...*) in Visual Studio Code so that **Ctrl+Shift+B** builds and uploads the firmware.

# Links
*  [Arduino CLI download and installation](https://arduino.github.io/arduino-cli/installation)
* [Integrate with External Tools via Tasks](https://code.visualstudio.com/docs/editor/tasks#vscode)
*  [Efficient Arduino Programming with Arduino CLI and Visual Studio Code](https://learn.sparkfun.com/tutorials/efficient-arduino-programming-with-arduino-cli-and-visual-studio-code/all)




