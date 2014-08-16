# Protokoll Beschreibung
===========

Ein sehr einfach gehaltenes Kommunikationsprotokoll. Das Protokoll wird für schulische Zwecke genutzt und dient zum lernen.

code api

## Aufbau

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
|1| initialisierung     |
|2| Ziel ID             |
|3| Source ID           |
|4| command(text) + textlänge  |
|5| TEXT (max 128byte)  |
|6| Checksumme          |

### Command übermitteln

Beim Command übermitteln wird bei dem command byte()

### Text übermitteln


