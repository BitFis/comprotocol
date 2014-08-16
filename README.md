# Protokoll Beschreibung
===========

Ein sehr einfach gehaltenes Kommunikationsprotokoll. Das Protokoll wird für schulische Zwecke genutzt und dient zum lernen.

## Aufbau

Des Prtokoll ist wie folgt aufgebaut:

1. Entweder kann man einfach einen Command senden

| 1 Byte              |
| :-----------------: |
| initialisierung     |
| Ziel ID             |
| Source ID           |
| command (max 127)   |
| Checksumme          |

2. Oder einen Text übermitteln

| 1 Byte              |
| :-----------------: |
| initialisierung     |
| Ziel ID             |
| Source ID           |
| command(text) + textlänge  |
| TEXT (max 128byte)  |
| Checksumme          |
