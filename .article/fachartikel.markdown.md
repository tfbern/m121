---
author: Samuel Hess
bibliography: quellen.bib
classoption:
- a4paper
- 12pt
csl: 'din-1505-2-numeric.csl'
date: 12. Mai 2020
documentclass: scrartcl
lang: de
link-citations: true
subject: 'ICT Modul 121 - Steuerungsaufgaben bearbeiten'
title: Steuerung eines Arduino Uno Mikrokontrollers via WebSocket
urlcolor: blue
---

Abstract
========

In der vorliegenden Arbeit wurde untersucht, wie ein Arduino Uno über
eine WebSocket-Verbindung gesteuert werden kann, während dieser im
Sekundentakt Statusmeldungen versendet.

Der verwendete Funduino Uno R3 [@lernset] verfügt über keine
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
Bartmann [@bartmannArduino] [@bartmannESP8266] [@bartmannESP32].

### Arduino mit integriertem WLAN

Der Arduino Uno hat keine eingebaute WLAN Schnittstelle. Es gibt jedoch
andere Arduino Modelle mit integriertem WLAN, wie z.B. der Arduino
MKR1000.

### WLAN Erweiterung

Mehrere Autoren berichten [@temperatureDashboard]
[@websocketcommunication], wie der Arduino mit dem dem WLAN Modul
ESP8266 erweitert werden kann.

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

![Prinzipskizze](img/prinzipskizze.png)

Hardware
--------

Verwendet wurde das Lernset Nr. 8 von Funduino [@lernset]. Darin
enthalten ist ein Funduino Uno. Weiter benötigen wir den
Temparatursensor TMP36 und den Fotowiderstand.

### Anschluss der Sensoren

![Anschluss der Sensoren](img/anschluss.png)

Software
--------

### Entwicklungsumgebung

Zur Entwicklung wurde folgende Software eingesetzt.

-   Visual Studio Code [@vscode] mit der Erweiterung C/C++ IntelliSense
    [@intellisense]
-   Arduino CLI [@arduinoCli]
-   Git for Windows [@gitForWindows] und TortoiseGit [@tortoiseGit]

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

-   Arduino Library (Arduino.h) [@sprachreferenz] [@codeReferenz]
    [@arduinoCheatSheet]\
-   AVR Libc [@avrlibc]

### Arduino Sketch

Zunächst müssen wir klären, in welcher Programmiersprache die Arduino
Sketches geschrieben werden. Nachdem man sich die Build-Umgebung genauer
unter die Lupe genommen hat, wird klar, dass keine eigene
Arduino-Sprache existiert[@arduinoLanguage]. Im Hintergrund wird aus dem
Sketch eine C++ Datei erstellt und mit *avr-g++* kompiliert.

Die Problematik der Heap-Fragmentierung wird von mehreren Autoren
aufgeworfen und diskutiert [@heapFragmentation][@heapFragmentation2].
Matt ist der Meinung, dass man deshalb auf die String Klasse in der
Arduino Library gänzlich verzichten soll [@arduinoStrings]. In der
Konsequenz müsste man die Stringfunktion aus der Standard C Library
[@avrlibc] verwenden und in C programmieren. Ich sehe dies nicht ganz so
eng und setze die Arduino String Klasse trotzdem, jedoch mit
Zurückhaltung ein. Ich befolge Matt's Rat, die Variablen by Reference zu
übergeben [@arduinoStrings].

Der Quellcode befindet sich im Ordner Arduino. Darin befinden sich
verschiedene Sketech, darunter
[genericReadWrite](../../arduino/genericReadWrite/genericReadWrite.ino)

### Serial Gateway

Der Quellcode befindet sich im Ordner
[Gateway](../../gateway/gateway.js).

### WebSocket Server

Der Quellcode befindet sich im Ordner
[WebSocketServer](../../websocketserver/websocketserver.js).

### Web GUI

Der Quellcode befindet sich im Ordner [Client](../../client/index.html).

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

Quellenverzeichnis {#quellenverzeichnis .unnumbered}
==================
