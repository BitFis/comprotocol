# Protokoll Beschreibung (comprotocol)
===========

Ein sehr einfach gehaltenes Kommunikationsprotokoll. Das Protokoll wird für schulische Zwecke genutzt und dient zum lernen.

code api

## Protokoll Aufbau

Des Prtokoll ist wie folgt aufgebaut:

1. Entweder kann man einfach einen Command senden

|| 1 Byte              |
|--:| :-----------------: |
|1| initialisierung     |
|2| Ziel ID             |
|3| Source ID           |
|4| command (max 127)   |
|5| Checksumme          |

2. Oder einen Text übermitteln

|| 1 Byte              |
|--:| :-----------------: |
|1| [Initialisierung](#Initialisierung)      |
|2| Ziel ID             |
|3| Source ID           |
|4| command(text) + textlänge  |
|5| TEXT (max 128byte)  |
|6| Checksumme          |

### Keine Übermittlung

Bei keiner Überittlung wird die Verbindung immer auf 1 gehalten.
Wichtig beim lesen und schreiben von Nachrichten muss dieser Wert umgekehrt (1 auf 0) gesetzt werden.
Bei dieser Dokumentation wird davon ausgegangen, dass das ausgehende oder eingehende Byte bereits umgekehrt, also 0 bei keinem Senden erhält.

### Initialisierung(#Initialisierung)

Um zu erkennen, dass eine Nachricht übermittelt wird, wird ein Initialisierungs Byte genutzt.
Dieses muss immer **1010 1010** betragen. Dies wird einheitlich bei allen Kontrollern, die dieses Protokoll nutzen.

### Ziel ID

Die Ziel ID ist eine 1 Byte grosse Zahl, die genutzt wird um zu erkennen, an wen man die Nachticht senden möchte.

### Source ID 

Die Source ID wird genutzt um zu erkenne, von wem die Nachricht ist und an wen man antworten sollte, sollte eine Antwort benötigt werden.

### Command übermitteln

Beim Command übermitteln wird bei dem command byte() das erste byte auf 0 gesetzt

### Text übermitteln


