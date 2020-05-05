<#
.DESCRIPTION
A longer description of your script.

.PARAMETER url
URL of the current Arduino CLI Release

.EXAMPLE
PS> Install-ArduinoCli
#>

Param(
  [string]$url = "https://github.com/arduino/arduino-cli/releases/download/0.10.0/arduino-cli_0.10.0_Windows_64bit.zip",
  [string]$installPath = $($env:APPDATA + '\npm')
)

$file = $Env:TEMP + '\arduino-cli.zip'
Invoke-WebRequest $url -OutFile $file
if (Test-Path $file) {
  Expand-Archive -Path $file -DestinationPath $installPath
  $file | Remove-Itemget
}

try {
  $(arduino-cli.exe version)
  Write-Host "Installation successful"
} catch {
  Write-Host "Installation failed"
}


