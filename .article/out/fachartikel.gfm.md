  - [Abstract](#abstract)
      - [Einleitung](#einleitung)
  - [Fragestellung](#fragestellung)
      - [Motivation](#motivation)
      - [Literatur-Review](#literatur-review)
          - [Arduino mit integriertem
            WLAN](#arduino-mit-integriertem-wlan)
          - [WLAN Erweiterung](#wlan-erweiterung)
          - [Serial Gateway](#serial-gateway)
  - [Experimenteller Teil](#experimenteller-teil)
      - [Informationsquellen](#informationsquellen)
      - [Prinzipskizze](#prinzipskizze)
      - [Hardware](#hardware)
          - [Anschluss der Sensoren](#anschluss-der-sensoren)
      - [Software](#software)
          - [Entwicklungsumgebung](#entwicklungsumgebung)
          - [Node Libraries](#node-libraries)
          - [Arduino Libraries](#arduino-libraries)
          - [Arduino Sketch](#arduino-sketch)
          - [Serial Gateway](#serial-gateway-1)
          - [WebSocket Server](#websocket-server)
          - [Web GUI](#web-gui)
  - [Resultate](#resultate)
  - [Diskussion](#diskussion)
  - [Zusammenfassung](#zusammenfassung)
  - [Danksagung](#danksagung)
  - [Interessenskonflikte](#interessenskonflikte)

# Abstract

In der vorliegenden Arbeit wurde untersucht, wie ein Arduino Uno über
eine WebSocket-Verbindung gesteuert werden kann, während dieser im
Sekundentakt Statusmeldungen versendet.

Der verwendete Funduino Uno R3 \[[1](#ref-lernset)\] verfügt über keine
WLAN-Schnittstelle. Daher erfolgt die WebSocket-Kommunikation extern auf
einem Gateway. Als Gateway wird ein Windows-PC verwendet. Arduino und
Gateway sind per USB verbunden und kommunizieren über eine virtuelle
serielle Schnittstelle.

Das Ergebnis zeigt, dass eine Steuerung eines Arduinos per WebSocket
problemlos möglich ist. Die eingehenden Nachrichten müssen auf dem
Arduino geparst werden. Dieses Parding ist einfacher, wenn das
verwendete Austauschformt schlank gehalten wird. Deshalb wurde anstelle
von JSON das URL Format verwendet.

## Einleitung

In diesem Kapitel wird die Motivation erläutert und genaue Fragesellung
definiert. Dann folgt eine kleine Übersichtsarbeit mit dazugehöriger
Literaturrecherche.

# Fragestellung

Welche Möglichkeiten gibt es, einen Arduino Uno via Websocket zu
steuern?

Während einer explorativen Online-Suche wurden einzelne Lösungen
gefunden. Eine systematische Zusammenstellung der Möglichkeiten fehlt
jedoch.

## Motivation

Die Motivation für die vorliegende Arbeit ist die Beantwortung der
nachfolgenden Fragestellung. Weiter soll der Artikel interessierten
Lesern als Einstiegslektüre diesen.

## Literatur-Review

Zum Thema existiert diverse Fachliteratur unter anderem von Erik
Bartmann\[[2](#ref-bartmannArduino)\]\[[3](#ref-bartmannESP8266)\]\[[4](#ref-bartmannESP32)\].

### Arduino mit integriertem WLAN

Der Arduino Uno hat keine eingebaute WLAN Schnittstelle. Es gibt jedoch
andere Arduino Modelle mit integriertem WLAN, wie z.B. der Arduino
MKR1000.

### WLAN Erweiterung

Mehrere Autoren
berichten\[[5](#ref-temperatureDashboard)\]\[[6](#ref-websocketcommunication)\],
wie der Arduino mit dem dem WLAN Modul ESP8266 erweitert werden kann.

### Serial Gateway

Eine weitere Möglichkeit, ist behelfsweise einen PC als Serial Gateway
einzusetzen. Mangels kurzfristig verfügbarer Hardware wollen wir diese
Option verfolgen.

# Experimenteller Teil

## Informationsquellen

Als Informationsquellen sind die Datenblätter zur jweiligen Hardware
sowie die Manuals zu den einsesetzten Softwarekomponenten zu nennen.

## Prinzipskizze

## Hardware

Verwendet wurde das Lernset Nr. 8 von Funduino\[[1](#ref-lernset)\].
Darin enthalten ist ein Funduino Uno. Weiter benötigen wir den
Temparatursensor TMP36 und den Fotowiderstand.

### Anschluss der Sensoren

## Software

### Entwicklungsumgebung

Zur Entwicklung wurde folgende Software eingesetzt.

  - Visual Studio Code\[[7](#ref-vscode)\] mit der Erweiterung C/C++
    IntelliSense\[[8](#ref-intellisense)\]

  - Arduino CLI\[[9](#ref-arduinoCli)\]

  - Git for Windows\[[10](#ref-gitForWindows)\] und
    TortoiseGit\[[11](#ref-tortoiseGit)\]

Nicht verwendet wurde die Arduino IDE. Windows verwendet den
Standardtreiber *usbser.sys* für den virtuellen COM Port.

### Node Libraries

Weiter wurde folgende NPM Packages eingesetzt:

  - WebSockets \[[12](#ref-websockets)\]

  - Express \[[13](#ref-express)\]

  - Chart.js \[[14](#ref-chartjs)\]

  - SerialPort \[[15](#ref-serialPort)\]

### Arduino Libraries

Weiter wurde folgende Arduino Libraries eingesetzt:

  - Arduino Library (Arduino.h)
    \[[16](#ref-sprachreferenz)\]\[[17](#ref-codeReferenz)\]\[[18](#ref-arduinoCheatSheet)\]

  - AVR Libc \[[19](#ref-avrlibc)\]

### Arduino Sketch

Zunächst müssen wir klären, in welcher Programmiersprache die Arduino
Sketches geschrieben werden. Nachdem man sich die Build-Umgebung genauer
unter die Lupe genommen hat, wird klar, dass keine eigene
Arduino-Sprache existert\[[20](#ref-arduinoLanguage)\]. Im Hintergrund
wird aus dem Sketch eine C++ Datei erstellt und mit *avr-g++*
kompiliert.

Die Problematik der Heap-Fragmentierung wird von mehreren Autoren
aufgeworfen und diskutiert \[[21](#ref-heapFragmentation)\]
\[[22](#ref-heapFragmentation2)\]. Matt ist der Meinung, dass man
deshalb auf die String Klasse in der Arduino Library gänzlich verzichten
soll\[[23](#ref-arduinoStrings)\]. In der Konsequenz müsste man die
Stringfunktion aus der Standard C Library\[[19](#ref-avrlibc)\]
verwerden und in C programmieren. Ich sehe dies nicht ganz so eng und
setze die Arduino String Klasse trotzdem, jedoch mit Zurückhaltung ein.
Ich befolge Matt’s Rat, die Variablen by Reference zu
übergeben\[[23](#ref-arduinoStrings)\].

Der Quellcode befindet sich im Anhang .

### Serial Gateway

Der Quellcode befindet sich im Anhang .

### WebSocket Server

Der Quellcode befindet sich im Anhang .

### Web GUI

Der Quellcode befindet sich im Anhang .

# Resultate

Es hat sich gezeigt, dass ein Seriell-zu-Websocket-Gatway unter Node.js
einfach zu implementieren ist. Über diesen Umweg kann der Arduino Uno
ans Internet angebunden werden.

# Diskussion

# Zusammenfassung

Statt des Arduino Uno könnte ein Arduino MKR1000 verwendet werden.
Dieser könnte kann auch an die Arduino Clound angebunden werden. Ein
weitere Option ist die Beschaffung einer WLAN Erweiterung wie das Modul
ESP8266.

# Danksagung

Ich danke den Lernenden der Klasse BINF2017A für die Zusammenarbeit.

# Interessenskonflikte

Das Projekt wurde im Rahmen des Beruffachschulunterrichts durchgeführt
und erhielt keine externde Finanzierung. Demnach bestehen keien
Interessenkonflikte.

<div id="refs" class="references hanging-indent">

<div id="ref-lernset">

\[1\] *Lernset Nr.8 mit UNO Controller - Kit für Arduino*. URL
<https://www.funduinoshop.com/epages/78096195.sf/de_DE/?ObjectPath=/Shops/78096195/Products/01-U8>

</div>

<div id="ref-bartmannArduino">

\[2\] <span class="smallcaps">Bartmann, Erik</span>: *Mit Arduino die
elektronische Welt entdecken*. 3. Aufl. : Bombini-Verlag, 2017
— ISBN [978-3-946496-00-7](https://worldcat.org/isbn/978-3-946496-00-7)

</div>

<div id="ref-bartmannESP8266">

\[3\] <span class="smallcaps">Bartmann, Erik</span>: *Das
ESP8266-Praxisbuch: Mit NodeMCU und ESPlorer* : Elektor Verlag, 2016
— ISBN [978-3-89576-321-2](https://worldcat.org/isbn/978-3-89576-321-2)

</div>

<div id="ref-bartmannESP32">

\[4\] <span class="smallcaps">Bartmann, Erik</span>: *Das
ESP32-Praxisbuch: Programmieren mit der Arduino-IDE* : Elektor Verlag,
2018
— ISBN [978-3-89576-333-5](https://worldcat.org/isbn/978-3-89576-333-5)

</div>

<div id="ref-temperatureDashboard">

\[5\] <span class="smallcaps">Andrew Shvayka, Igor Khanenko,
<span class="csl-no-smallcaps">Igor Kulikov</span></span>: *Temperature
Dashboard Using Arduino UNO, ESP8266 And MQTT*. URL
<https://www.hackster.io/thingsboard/temperature-dashboard-using-arduino-uno-esp8266-and-mqtt-5e26eb>

</div>

<div id="ref-websocketcommunication">

\[6\] *WebSocket communication with an ESP8266 or Arduino in Python.
Test with the ws4py library on Raspberry Pi*. URL
<https://diyprojects.io/websocket-communication-esp8266-arduino-python-test-ws4py-library-raspberry-pi/#.Xq6bKagzaUk>

</div>

<div id="ref-vscode">

\[7\] Visual Studio Code.

</div>

<div id="ref-intellisense">

\[8\] C/C++ IntelliSense, debugging, and code browsing.

</div>

<div id="ref-arduinoCli">

\[9\] Arduino CLI.

</div>

<div id="ref-gitForWindows">

\[10\] Git for Windows.

</div>

<div id="ref-tortoiseGit">

\[11\] TortoiseGit.

</div>

<div id="ref-websockets">

\[12\] Simple to use, blazing fast and thoroughly tested WebSocket
client and server for Node.js.

</div>

<div id="ref-express">

\[13\] Express Schnelles, offenes, unkompliziertes Web-Framework für
Node.js.

</div>

<div id="ref-chartjs">

\[14\] Simple yet flexible JavaScript charting for designers &
developers.

</div>

<div id="ref-serialPort">

\[15\] Node SerialPort.

</div>

<div id="ref-sprachreferenz">

\[16\] *Sprach-Referenz*

</div>

<div id="ref-codeReferenz">

\[17\] *Arduino Befehlsübersicht*

</div>

<div id="ref-arduinoCheatSheet">

\[18\] *Arduino Programming Cheat Sheet*

</div>

<div id="ref-avrlibc">

\[19\] *AVR Libc*

</div>

<div id="ref-arduinoLanguage">

\[20\] *C++ vs. The Arduino Language?* URL
<https://arduino.stackexchange.com/questions/816/c-vs-the-arduino-language>

</div>

<div id="ref-heapFragmentation">

\[21\] *What is Heap Fragmentation?* URL
<https://cpp4arduino.com/2018/11/06/what-is-heap-fragmentation.html>

</div>

<div id="ref-heapFragmentation2">

\[22\] <span class="smallcaps">Walls, Colin</span>: *Dynamic Memory
Allocation and Fragmentation in C and C++*. URL
<https://www.design-reuse.com/articles/25090/dynamic-memory-allocation-fragmentation-c.html>

</div>

<div id="ref-arduinoStrings">

\[23\] *The Evils of Arduino Strings*. URL
<https://majenko.co.uk/blog/evils-arduino-strings>

</div>

<div id="ref-literaturverzeichnis">

\[24\] *LaTeX: Literaturverzeichnis erstellen - so klappt’s*. URL
<https://www.heise.de/tipps-tricks/LaTeX-Literaturverzeichnis-erstellen-so-klappt-s-4401420.html#%C3%9Cberschrift_1>

</div>

<div id="ref-inhaltsverzeichnis">

\[25\] *LaTeX: Inhaltsverzeichnis anlegen - so geht’s*. URL
<https://www.heise.de/tipps-tricks/LaTeX-Inhaltsverzeichnis-anlegen-so-geht-s-4401672.html>

</div>

<div id="ref-arduino">

\[26\] *Arduino*. URL <https://www.arduino.cc/>

</div>

<div id="ref-funduino">

\[27\] *Kits und Anleitungen für Arduino* : Funduino Anleitungen

</div>

<div id="ref-howtocprogramstoredinram">

\[28\] *How C Program Stored in RAM*. URL
<https://arduino.stackexchange.com/questions/816/c-vs-the-arduino-language>

</div>

<div id="ref-speicherinembeddedsystems">

\[29\] *Speicher in Embedded Systems*. URL
<http://dodo.fb06.fh-muenchen.de/hermann/esII/es2-vl123-v12.pdf>

</div>

<div id="ref-buildinexamples">

\[30\] *builtInExamples*. URL
<https://www.arduino.cc/en/Tutorial/BuiltInExamples>

</div>

<div id="ref-texlive">

\[31\] TeX Live.

</div>

<div id="ref-latexWorkshop">

\[32\] <span class="smallcaps">Yu, James</span>: LaTeX Workshop.

</div>

<div id="ref-cProgramInRam">

\[33\] *How C Program Stored in RAM?* URL
<http://www.vishalchovatiya.com/how-c-program-stored-in-ram-memory>

</div>

<div id="ref-noDelay">

\[34\] *Blink Without Delay*. URL
<https://www.arduino.cc/en/tutorial/BlinkWithoutDelay>

</div>

</div>
