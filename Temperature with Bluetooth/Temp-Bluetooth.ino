/* 
 * BTserialDemo: A simple demo of sending and receiving data between serial monitor
 *               and HM-10.
 * Temperature alarm with led and toneMelody
 * https://dev.to/chrisdinhnz/getting-hm-10-ble-up-running-with-arduino-uno-1f02
 * 
 * References: https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html
 *             http://www.martyncurrey.com/hm-10-bluetooth-4ble-modules/
 *             https://drive.google.com/file/d/0BzFWfMiqqjyqdjFic281Vl80UFE/view
 *             https://makersportal.com/blog/2019/5/12/smartphone-arduino-weighing-scale-with-load-cell-and-hx711
 *
 */

#include <AltSoftSerial.h>
#include "pitches.h"

// constants won't change. They're used here to set pin numbers:
const int ledPin = 13; // the number of the LED pin
const int piezoPin = 8; // the number of the buzzer pin
// const int buttonPin = 2; // the number of the pushbutton pin

int value = 0;
float voltage = 0;
float temp = 0.00;
float warningTemp = 32.00;

// variables will change:
int delayLED;
int delayBetweenTempRead = 500;
// int buttonState = 0; // variable for reading the pushbutton status


AltSoftSerial ble_device(8,9); // CC2541 TX/RX pins

static void BluetoothDeviceAvailable(void){

  temp = readTemp();
  SendTempToSerial(temp);
  SendTempToBTSerial(temp);

  if(temp > warningTemp){ // if temperature > 30 degree celsius
    warningLEDAndSound();
  }

  delay(delayBetweenTempRead);
//  if (readStateOfButton() == true){
//  }


}

//static boolean readStateOfButton(){
//    if (buttonState == HIGH) {
//      return false;
//    }
//    else{
//      Serial.print("Button Pressed");
//      return true;
//    }
//}

static int readTemp(void){
  value = analogRead(A0);      // sensor output to arduino analog A0 pin
  voltage = value*0.00488;
  temp = voltage*100;

  pulseLED(50);
  return temp;
}

static void SendTempToSerial(float temp){
  Serial.print("TEMP:");
  Serial.println(temp);
}

static void SendTempToBTSerial(float temp){
  // ble_device.print("TEMP: ");
  ble_device.print("\n");
  ble_device.print(temp);
  ble_device.print(" ");
}

static void pulseLED(int delayLED){
  Serial.println("LED ON");
  digitalWrite(ledPin, HIGH); // switch ON LED
  delay(delayLED);
  Serial.println("LED OFF");
  digitalWrite(ledPin, LOW); // switch OFF LED
}

static void warningLEDAndSound(void){
  digitalWrite(ledPin, HIGH);
  tone(piezoPin, NOTE_B4, 500);
  delay(500);
  digitalWrite(ledPin, LOW);
  tone(piezoPin, NOTE_C4, 500);
  delay(500);
  noTone(piezoPin);
}

void setup ()
{
  Serial.begin(9600);
  ble_device.begin(9600);
  Serial.println("BTserial started at 115200");
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the buzzer pin as an output:
  pinMode(piezoPin, OUTPUT);
  // initialize the pushbutton pin as an input:
//  pinMode(buttonPin, INPUT_PULLUP);
}

void loop ()
{
  if (ble_device.available()){
    BluetoothDeviceAvailable();
  }
  if (Serial.available()){
    BluetoothDeviceAvailable();
  }
}
