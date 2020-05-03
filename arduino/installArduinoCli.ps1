 $url = 'https://github.com/arduino/arduino-cli/releases/download/0.10.0/arduino-cli_0.10.0_Windows_64bit.zip'
 $tmp = 'arduino-cli.zip'
 Invoke-WebRequest $url -OutFile $tmp
 Expand-Archive -Path $tmp -DestinationPath  $($env:APPDATA + '\npm')
 $tmp | Remove-Itemget