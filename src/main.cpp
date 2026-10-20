#include <Arduino.h>
#include <BleKeyboard.h>

// So erscheint der ESP in der Bluetooth-Liste: Name, Hersteller, Akkustand
BleKeyboard bleKeyboard("ESP32 Lautstaerke", "Joana Dorer", 11);

const int TOUCH_PIN = 4;   // GPIO 4 = Touch-Pin T0
const int SCHWELLE  = 60;  // Wert UNTER der Schwelle = "beruehrt" 

bool warBeruehrt = false;  // merkt sich: war der Pin beim letzten Durchlauf beruehrt?

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();     // Bluetooth-Tastatur starten
  Serial.println("Warte auf Bluetooth-Verbindung...");
}

void loop() {
  int wert = touchRead(TOUCH_PIN);
  bool istBeruehrt = wert < SCHWELLE;

  // Nur im MOMENT des Beruehrens reagieren:
  // jetzt beruehrt UND vorher nicht beruehrt
  if (istBeruehrt && !warBeruehrt) {
    Serial.print("Beruehrt! Wert: ");
    Serial.println(wert);

    if (bleKeyboard.isConnected()) {
      bleKeyboard.write(KEY_MEDIA_VOLUME_UP);  // Lauter-Taste senden
      Serial.println("-> Lautstaerke +1");
    } else {
      Serial.println("-> Nicht verbunden, nichts gesendet");
    }
  }

  warBeruehrt = istBeruehrt;  // Zustand fuer den naechsten Durchlauf merken
  delay(50);
}