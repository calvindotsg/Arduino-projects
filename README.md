# Proof of concepts
Python code for quick prototyping of various suitable functions in physical computing with Arduino, with aim of building applications useful in restaurant setting.

## Projects in this repository
### Temperature alarm with led and tone melody  
1. Temperature monitored every second with temperature sensor wired to Arduino Uno.
2. When temperature exceeds pre-determined threshold, tone melody and led is triggered.
### Temperature with Bluetooth
1. Temperature monitored every second with temperature sensor wired to Arduino Uno.
2. Temperature values are sent in real time over Arduino's bluetooth HM-10 module to Smartphone.
3. Temperature values displayed in real time on compatible application.
### Temperature only
1. Temperature monitored every second with temperature sensor.
2. Temperature values displayed in real time in Arduino console.
### Bluetooth with Tone melody
1. User enters a predetermined character (trigger) on Smartphone running compatible application.
2. Trigger data sent in real time over to Arduino's bluetooth HM-10 module.
3. Onboard beeper on the Arduino Uno plays the corresponding tone melody to the different trigger data received from bluetooth HM-10 module.
### Button
1. When Arduino uno's onboard button is pressed, onboard LED lights up.