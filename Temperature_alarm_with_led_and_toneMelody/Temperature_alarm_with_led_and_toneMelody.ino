/*
  Temperature alarm with led and toneMelody
 
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8
*/

#include "pitches.h"

const int ledPin = 2;
const int piezoPin = 8;
float celsius = 0.00;



void setup() {
 Serial.begin(9600);
 pinMode(ledPin, OUTPUT);
 pinMode(piezoPin, OUTPUT);
}

void loop() {
 celsius = analogRead(A0) * 0.488;
 Serial.print("TEMP:");
 Serial.println(celsius);
 if(celsius > 30){ // if temperature > 30 degree celsius
    digitalWrite(ledPin, HIGH);
    tone(piezoPin, NOTE_B4, 500);
    delay(500);
    digitalWrite(ledPin, LOW);
    tone(piezoPin, NOTE_C4, 500);
    delay(500);
    noTone(piezoPin);
  }
  delay(500);
}
