/*
 * BTserialDemo: A simple demo of sending and receiving data between serial monitor
 *               and HM-10.
 * 
 * References: https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html
 *             http://www.martyncurrey.com/hm-10-bluetooth-4ble-modules/
 *
 */

#include <AltSoftSerial.h>
#include "pitches.h"

static AltSoftSerial btSerial;

const int ledPin = 2;
const int piezoPin = 8;
//float celsius = 0.00;

/* There is data waiting to be read from the HM-10 device. */
static void HandleRxDataIndication(void)
{
   char c = btSerial.read();

   /* Just echo the character for now. */
   Serial.write(c);

   if ( c == '0') {
    Serial.println("LED OFF");
    digitalWrite(ledPin, LOW); // switch OFF LED
    tone(piezoPin, NOTE_C4, 500);
    delay(500);
    }
   
   if ( c == '1') {
    Serial.println("LED ON");
    digitalWrite(ledPin, HIGH); // switch OFF LED
    delay(500);
    tone(piezoPin, NOTE_B4, 500);

    /*
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
    */
    
  }
}

/* There is data waiting to be sent to the HM-10 device. */
static void HandleTxDataIndication(void)
{
   char c = Serial.read();

   /* Echo the character just been sent. */
   Serial.write(c);

   /* We don't send carriage return or line feed. */
   if (c == 0x0A || c == 0x0D)
   {
      return;
   }

   if ( c == '0') {
    Serial.println("LED OFF");
    digitalWrite(ledPin, LOW); // switch OFF LED
    tone(piezoPin, NOTE_C4, 500);
    delay(500);
    }
   
   if ( c == '1') {
    Serial.println("LED ON");
    digitalWrite(ledPin, HIGH); // switch OFF LED
    delay(500);
    tone(piezoPin, NOTE_B4, 500);
  }

   btSerial.write(c);
}

void setup()
{
  Serial.begin(9600);
  btSerial.begin(9600);
  Serial.println("BTserial started at 115200");
  pinMode(ledPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);
}

void loop()
{
   if (btSerial.available())
   {
      HandleRxDataIndication();
   }

   if (Serial.available())
   {
      HandleTxDataIndication();
   }
}
