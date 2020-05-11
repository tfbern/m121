---
documentclass: scrartcl
classoption:
- a4paper
- 12pt
lang: de
title: "Arduino IoT Tutorial"
author: "Samuel Hess"
date: "11. Mai 2020"
toc: true
urlcolor: blue
pandoc_args: --listings
nocite: '@*'
csl: eva-berlin-konferenz.csl
bibliography: ./_doc/quellen.bib
header-includes: | 
  ```{=latex}
  \usepackage{listings}
  \lstset{backgroundcolor=\color{gray}}
  \lstset{breaklines, frame=single, numbers=left, numberstyle=\tiny}
  \definecolor{bgcolor}{rgb}{0.95,0.95,0.95}
  \definecolor{mygreen}{rgb}{0,0.6,0}
  \definecolor{mygray}{rgb}{0.5,0.5,0.5}
  \definecolor{mymauve}{rgb}{0.58,0,0.82}
  \lstset{ %
    backgroundcolor=\color{bgcolor}, % choose the background color
    basicstyle=\footnotesize,        % size of fonts used for the code
    breaklines=true,                 % automatic line breaking only at whitespace
    captionpos=b,                    % sets the caption-position to bottom
    commentstyle=\color{mygreen},    % comment style
    escapeinside={\%*}{*)},          % if you want to add LaTeX within your code
    keywordstyle=\color{blue},       % keyword style
    stringstyle=\color{mymauve},     % string literal style
    caption=\lstname,                % show the filename of files included with \lstinputlisting; also try caption instead of 
    captionpos=b,                    % sets the caption-position to bottom
  }
  ```
---


Abstract
========

In der vorliegenden Arbeit wurde untersucht, wie ein Arduino Uno über
eine WebSocket-Verbindung gesteuert werden kann, während dieser im
Sekundentakt Statusmeldungen versendet.

Der verwendete Funduino Uno R3[@lernset] verfügt über keine
WLAN-Schnittstelle. Daher erfolgt die WebSocket-Kommunikation extern auf
einem Gateway. Als Gateway wird ein Windows-PC verwendet. Arduino und
Gateway sind per USB verbunden und kommunizieren über eine virtuelle
serielle Schnittstelle.

Das Ergebnis zeigt, dass eine Steuerung eines Arduinos per WebSocket
problemlos möglich ist. Die eingehenden Nachrichten müssen auf dem
Arduino geparst werden. Dieses Parding ist einfacher, wenn das
verwendete Austauschformt schlank gehalten wird. Deshalb wurde anstelle
von JSON das URL Format verwendet.

Einleitung
==========

In diesem Kapitel wird die Motivation erläutert und genaue Fragesellung
definiert. Dann folgt eine kleine Übersichtsarbeit mit dazugehöriger
Literaturrecherche.

Fragestellung
-------------

Welche Möglichkeiten gibt es, einen Arduino Uno via Websocket zu
steuern?

Während einer explorativen Online-Suche wurden einzelne Lösungen
gefunden. Eine systematische Zusammenstellung der Möglichkeiten fehlt
jedoch.

Motivation
----------

Die Motivation für die vorliegende Arbeit ist die Beantwortung der
nachfolgenden Fragestellung. Weiter soll der Artikel interessierten
Lesern als Einstiegslektüre diesen.

Literatur-Review
----------------

Zum Thema existiert diverse Fachliteratur unter anderem von Erik
Bartmann[@bartmannArduino][@bartmannESP8266][@bartmannESP32].

### Arduino mit integriertem WLAN

Der Arduino Uno hat keine eingebaute WLAN Schnittstelle. Es gibt jedoch
andere Arduino Modelle mit integriertem WLAN, wie z.B. der Arduino
MKR1000.

### WLAN Erweiterung

Mehrere Autoren
berichten[@temperatureDashboard][@websocketcommunication], wie der
Arduino mit dem dem WLAN Modul ESP8266 erweitert werden kann.

### Serial Gateway

Eine weitere Möglichkeit, ist behelfsweise einen PC als Serial Gateway
einzusetzen. Mangels kurzfristig verfügbarer Hardware wollen wir diese
Option verfolgen.

Experimenteller Teil
====================

Informationsquellen
-------------------

Als Informationsquellen sind die Datenblätter zur jweiligen Hardware
sowie die Manuals zu den einsesetzten Softwarekomponenten zu nennen.

Prinzipskizze
-------------

Hardware
--------

Verwendet wurde das Lernset Nr. 8 von Funduino[@lernset]. Darin
enthalten ist ein Funduino Uno. Weiter benötigen wir den
Temparatursensor TMP36 und den Fotowiderstand.

### Anschluss der Sensoren

Software
--------

### Entwicklungsumgebung

Zur Entwicklung wurde folgende Software eingesetzt.

-   Visual Studio Code[@vscode] mit der Erweiterung C/C++
    IntelliSense[@intellisense]

-   Arduino CLI[@arduinoCli]

-   Git for Windows[@gitForWindows] und TortoiseGit[@tortoiseGit]

Nicht verwendet wurde die Arduino IDE. Windows verwendet den
Standardtreiber *usbser.sys* für den virtuellen COM Port.

### Node Libraries

Weiter wurde folgende NPM Packages eingesetzt:

-   WebSockets [@websockets]

-   Express [@express]

-   Chart.js [@chartjs]

-   SerialPort [@serialPort]

### Arduino Libraries

Weiter wurde folgende Arduino Libraries eingesetzt:

-   Arduino Library (Arduino.h)
    [@sprachreferenz][@codeReferenz][@arduinoCheatSheet]

-   AVR Libc [@avrlibc]

### Arduino Sketch

Zunächst müssen wir klären, in welcher Programmiersprache die Arduino
Sketches geschrieben werden. Nachdem man sich die Build-Umgebung genauer
unter die Lupe genommen hat, wird klar, dass keine eigene
Arduino-Sprache existert[@arduinoLanguage]. Im Hintergrund wird aus dem
Sketch eine C++ Datei erstellt und mit *avr-g++* kompiliert.

Die Problematik der Heap-Fragmentierung wird von mehreren Autoren
aufgeworfen und diskutiert [@heapFragmentation][@heapFragmentation2].
Matt ist der Meinung, dass man deshalb auf die String Klasse in der
Arduino Library gänzlich verzichten soll[@arduinoStrings]. In der
Konsequenz müsste man die Stringfunktion aus der Standard C
Library[@avrlibc] verwerden und in C programmieren. Ich sehe dies nicht
ganz so eng und setze die Arduino String Klasse trotzdem, jedoch mit
Zurückhaltung ein. Ich befolge Matt's Rat, die Variablen by Reference zu
übergeben[@arduinoStrings].

Der Quellcode befindet sich im Kapitel
[10.1](#Arduino Sketch){reference-type="ref"
reference="Arduino Sketch"}.

### Serial Gateway

Der Quellcode befindet sich im Kapitel
[10.2](#Serial Gateway){reference-type="ref"
reference="Serial Gateway"}.

### WebSocket Server

Der Quellcode befindet sich im Kapitel
[10.3](#WebSocket Server){reference-type="ref"
reference="WebSocket Server"}.

### Web GUI

Der Quellcode befindet sich im Kapitel
[10.4](#Web Client){reference-type="ref" reference="Web Client"}.

Resultate
=========

Es hat sich gezeigt, dass ein Seriell-zu-Websocket-Gatway unter Node.js
einfach zu implementieren ist. Über diesen Umweg kann der Arduino Uno
ans Internet angebunden werden.

Diskussion
==========

Zusammenfassung
===============

Statt des Arduino Uno könnte ein Arduino MKR1000 verwendet werden.
Dieser könnte kann auch an die Arduino Clound angebunden werden. Ein
weitere Option ist die Beschaffung einer WLAN Erweiterung wie das Modul
ESP8266.

Danksagung
==========

Ich danke den Lernenden der Klasse BINF2017A für die Zusammenarbeit.

Interessenskonflikte
====================

Das Projekt wurde im Rahmen des Beruffachschulunterrichts durchgeführt
und erhielt keine externde Finanzierung. Demnach bestehen keien
Interessenkonflikte.

Quellenverzeichnis
==================

Quellcode
=========
```
{{article.md}}
```

Arduino Sketch {#Arduino Sketch}
--------------

```c++
/*
  This sketch periodically reads all analog inputs and logs the values in JSON format to the serial line.
  In addition it will listen to the serial line and process any incoming messages.
  To compile and upload this sketch from the arduino folder execute 'arduino-cli compile genericReadWrite -u' 
  The options -b and -p will be taken automatically from sketch.json
  Upload is not possible while server.js is running because it uses the serial line also.

  The digital pins are named from 0 to 13. DIO 13 and the built-in LED are connected.
  Digital pins 0 and 1 should be avoided as they are internally conneted to the serial line.
  The analog pins A0 to A5 habe the IDs 14 to 19. 
  Hence, in order to query all IO states (digital and analog) we can make a loop from 0 to 19
*/
#include <Arduino.h>
#include "status.h"
#include "control.h"

// global variables
unsigned long previousMillis = 0;   // count loops
const long interval = 1000;         // interval at which to send IO status updates (milliseconds)

// initialisation
void setup(){
  // init serial line with 9600 baud
  Serial.begin(9600);
  // init all digital pins
  for (int i = 0; i <= 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

// main
void loop() {
  // ckeck if we have incoming message, i.e. check if something is in the serial buffer
  if (Serial.available() > 0) {
    // receive messages on serial line, parse and handle the messages
    processSerialInput();
    // send updated IO states to host
    Serial.println(readPins());
  } else {
    // get the milliseconds since start
    unsigned long currentMillis = millis();
    // do only something if interval time has passed
    if (currentMillis - previousMillis >= interval)  { 
      // save the last time we sent the IO states
      previousMillis = currentMillis;
      // send IO states to host
      Serial.println(readPins());
    } 
  }
} 
```

### Funktionen zur Statusausgabe

```c++
#include <Arduino.h>
#include "status.h"

// get status of all pin ans make JSON object, e.g. {"D0":1, ... , "A0":1023}
String readPins() {
  String ioStates = "{";
  for (int i = 0; i <= 19; i++) {
    ioStates += (i <= 13) ? "\"D" : "\"A";
    ioStates += (i <= 13) ? i : i-14;
    ioStates += "\":";
    ioStates += (i <= 13) ? digitalRead(i) : analogRead(i); 
    ioStates += (i == 19) ? "" : ",";
  }
  ioStates += "}";
  return ioStates;
}
```

### Funktionen zur Steuerung

```c++
#include <Arduino.h>
#include "control.h"

// process incoming messages
void processSerialInput() {
  String incomingMessage;                 // e.g. 0=1&2=0&3=1
  String keyValuePair;                    // splitted at &
  incomingMessage = Serial.readString();  // read the whole String in the serial buffer
  while (true) {
    // get the next key-value pair to process
    int pos = incomingMessage.indexOf('&');
    if (pos != -1) { 
      // '&' is present, we have multiple key-value pairs
      keyValuePair = incomingMessage.substring(0,pos); // get the first key-value pair
      processCommand(keyValuePair); // process it
      incomingMessage = incomingMessage.substring(pos+1); // and remove it from incomingMessage
    } else {
      // just one command or last command
      processCommand(incomingMessage); // process it
      break;
    }
  }
}

// process key-value pair 
void processCommand(String &command) {  // &command makes receiving the String object by reference, hence avoid copies and save resources
  int pos = command.indexOf('=');
  if (command.length() > 2 && pos > 0 ) { // min 3 characters with '=' present at minimum second position
    int pin = command.substring(0,pos).toInt(); // characters before '='
    int state = command.substring(pos+1).toInt(); // characters after '='
    if (pin >= 0 && pin <= 19 && ( state == 0 || state == 1 )) {
      // Serial.println("Setting input " + key + " to " + value);
      digitalWrite(pin, state);
    }
  }
}
```

Serial Gateway {#Serial Gateway}
--------------

```js
// serial gateway
const url = 'ws://websocksrv.herokuapp.com'
const WebSocket = require('ws');
const ws = new WebSocket(url);
const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const serial = new SerialPort('COM3', { baudRate: 9600 })
const parser = new Readline()
// forwarding messages from serial to websocket
serial.pipe(parser)
parser.on('data', function (line) {
  try {
    var obj = JSON.parse(line)
    ws.send(line);
  } catch(err) {
    // console.log(err)
    console.log('gateway parse error: skipping malformed data')
  }
})
// forwarding messages from websocket to serial
ws.on('open', function() {
  console.log('Connected to ' + url)
})
ws.on('message', function(message) {
  console.log('gateway forwarding command to Arduino: ' + message)
  serial.write(message)
})
```

WebSocket Server {#WebSocket Server}
----------------

```js
// WebSocket server
const port = process.env.PORT || 81 
const WebSocket = require('ws');
const wss = new WebSocket.Server({ port: port });
wss.on('connection', function connection(ws) {
  ws.on('message', function incoming(data) {
    wss.clients.forEach(function each(client) {
      if (client !== ws && client.readyState === WebSocket.OPEN) {
        client.send(data);
      }
    });
  });
});
```

Web Client {#Web Client}
----------

```html
<!DOCTYPE html>
<html>
<head>
  <title>Arduino IoT Demo App</title>
  <link href="https://unpkg.com/material-components-web@v4.0.0/dist/material-components-web.min.css" rel="stylesheet">
  <link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons">
  <script src="https://unpkg.com/material-components-web@v4.0.0/dist/material-components-web.min.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/chart.js@2.8.0"></script>
</head>
<body onload="init()">
  <div class="mdc-layout-grid">
    <h2>Configure WebSocket Server</h2>
    <input id="wsurl" type="text" size="50" value="ws://websocksrv.herokuapp.com">
    <input type="button" value="configure" onclick="init()">
    <p id="help"></p>
    <h2>Switch Arduino Digital Outputs</h2>
    <select id="pin">
      <option value=all>all</option>
    </select>&nbsp;
    <select id="state">
      <option value=0>low</option>
      <option value=1>high</option>
    </select>&nbsp;
    <input type="button" value="send" onclick="sendCommand()">
    <div id="container" style="width: 80%;">
      <h2>Temperatur</h2>
      <canvas id="myChart1"></canvas>
    </div>
    <div id="container" style="width: 80%;">
      <br>
      <h2>Analogue Inputs</h2>
      <canvas id="myChart2"></canvas>
    </div>
    <div id="container" style="width: 80%;">
      <br>
      <h2>Digital Inputs</h2>
      <canvas id="myChart3"></canvas>
    </div>
  </div>
</body>

<script>
// const url = 'ws://localhost:81'
var url = null
var ws = null
var temperatures = []
var timestamps = []
var log = false

function init(){
  wsurl = document.getElementById("wsurl").value
  createWebsocket(wsurl)

  var x = document.getElementById("pin");
  for (i=0; i<=13; i++) {
    var option = document.createElement("option");
    option.text = "Digital Output " + i;
    option.value = i;
    x.add(option);
  }
  document.getElementById("help").innerHTML = 
  'This page will open a WebSocket connection to ' + wsurl + '. </br>' +
  'Through the socket we will receive JSON objects with status information. This page displays the received status information with charts.</br>' +
  'Also, we can send commands to Arduino through the socket, e.g. switch an output. </br>' +
  'In Chrome press F12 for further details.'
}
function sendCommand(){
  var pin = document.getElementById('pin').value
  var state = document.getElementById('state').value
  var command = '';
  if (pin == 'all') {
    for (i=0; i <= 13; i++) {
      command+= i + "=" + state
      command+= ( i == 13 ) ? '' : '&'
    }
  } else {
    command = pin + "=" + state
  }
  console.log(command)
  ws.send(command)
}

function calculateTemperature(adcValue) {
  return adcValue/1023*5*100 - 50
}

function createTimestamp() {
  return new Date().toISOString().slice(0,19).replace("T"," ")
}

function processIncomingMessages(event) {
  try {
    var ioStates = JSON.parse(event.data)
    if (log) {
      console.log(ioStates);
    }

    // update temperature chart
    temperatures.push(calculateTemperature(ioStates.A0))
    timestamps.push(createTimestamp())
    updateChart(chart1, timestamps, temperatures)
    
    // update IO charts
    var keys = Object.keys(ioStates)
    var values = Object.values(ioStates)
    updateChart(chart3, keys.slice(0,14), values.slice(0,14))   // digital states
    updateChart(chart2, keys.slice(14,20), values.slice(14,20)) // analog states
  } catch(err) {
      console.log('skipping invalid JSON package "' + event.data + '" from ' + event.origin )
      // console.log(err); // error in the above string (in this case, yes)!
  }
}

function createWebsocket(url) {
  temperatures = []
  timestamps = []
  ws = new WebSocket(url);
  ws.onopen = function() {
      console.log('WebSocket connection to ' + url + ' established');
      console.log('type "log=true" to log incoming JSON objects');
      console.log('type "ws.send("13=1")"" to switch the build-in LED on');
  };
  // handle messages from server
  ws.onmessage = processIncomingMessages
}

function createChart(ctx, type, label)  {
  var chart = new Chart(ctx, {
      // The type of chart we want to create
      type: type,
      // The data for our dataset
      data: {
          labels: [],
          datasets: [{
              label: label,
              backgroundColor: 'rgb(255, 99, 132)',
              borderColor: 'rgb(255, 99, 132)',
              data: []
          }]
      },
  });
  return chart
}
function updateChart(chart, xValues, yValues) {
  if (xValues && yValues) {
    chart.data.labels = xValues
    chart.data.datasets[0].data = yValues
    chart.update();
  }
} 

var ctx1 = document.getElementById('myChart1').getContext('2d');
var ctx2 = document.getElementById('myChart2').getContext('2d');
var ctx3 = document.getElementById('myChart3').getContext('2d');

var chart1 = createChart(ctx1, 'line', 'Temperatursensor an A0')
chart1.options.scales.yAxes[0].ticks.suggestedMin = -50
chart1.options.scales.yAxes[0].ticks.suggestedMax = 150
chart1.data.datasets[0].fill = false

var chart2 = createChart(ctx2, 'bar', 'Analog Inputs')
chart2.options.scales.yAxes[0].ticks.min = 0
chart2.options.scales.yAxes[0].ticks.max = 1024
chart2.options.scales.yAxes[0].ticks.stepSize = 128

var chart3 = createChart(ctx3, 'bar', 'Digital Inputs')
chart3.options.scales.yAxes[0].ticks.min = 0
chart3.options.scales.yAxes[0].ticks.max = 1
chart3.options.scales.yAxes[0].ticks.stepSize = 1


</script>
</html>
```