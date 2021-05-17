int ldrPin = 7;
int value = 0;
float voltage = 0;
float temp = 0;

void setup ()
{
Serial.begin(9600);
}

void loop ()
{
value = analogRead(A0);      // sensor output to arduino analog A0 pin
voltage = value*0.00488;
temp = voltage*100;
Serial.print("TEMP:");
Serial.println(temp);

delay(500);
}
