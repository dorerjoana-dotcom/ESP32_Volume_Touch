# ESP32 Touch-Lautstärkeregler

Ein ESP32 als Bluetooth-Tastatur: Bei jeder Berührung von **Pin 4** wird die Lautstärke des Laptops um **eine Stufe erhöht**.

Projekt für *Creative Coding 2* 
von Joana Dorer

## Demo-Video

[JoanaDorer.mp4](JoanaDorer.mp4)

## Hardware

- ESP32 DevKit (WROOM)
- USB-C-Kabel (Datenkabel)
- 1 Jumper-Draht an **GPIO 4** (Touch-Pin T0) als Berührungsfläche

## Funktionsweise

1. Der ESP32 misst mit `touchRead(4)` laufend den Touch-Wert an Pin 4.
   - ohne Berührung: ca. 114
   - mit Berührung: ca. 10–15
2. Liegt der Wert unter der **Schwelle von 60**, gilt der Pin als berührt.
3. Nur im **Moment der Berührung** (vorher nicht berührt → jetzt berührt) wird einmal die Taste `KEY_MEDIA_VOLUME_UP` gesendet. Wer den Finger liegen lässt, löst keine weiteren Stufen aus.
4. Die Taste wird über die Library [ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard) per Bluetooth an den Laptop geschickt. Der Laptop erkennt den ESP als normale Tastatur.

## Installation

1. Projekt in **VS Code** mit der Erweiterung **PlatformIO** öffnen
2. ESP32 per USB anschließen und auf **Upload** (→) klicken
   (falls `Connecting...` hängt: BOOT-Taste am ESP gedrückt halten)
3. Am Laptop unter **Bluetooth** das Gerät **„ESP32 Lautstaerke“** verbinden
4. Draht an Pin 4 antippen → Lautstärke geht hoch 🔊

Falls die Berührung nicht zuverlässig erkannt wird, kann der Wert `SCHWELLE` in `src/main.cpp` angepasst werden. Die aktuellen Werte zeigt der Serial Monitor (115200 Baud).

## Dateien

| Datei | Inhalt |
|---|---|
| `src/main.cpp` | Programm-Code |
| `platformio.ini` | Board-Einstellungen und Library |
| `JoanaDorer.mp4` | Dokumentations-Video |