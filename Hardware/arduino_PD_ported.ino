/*
RedHawk Endeavor, AY16-2
file   : arduino_PD_ported.ino
author : Nicholas Treiberg
xnumber: x62889
*/

//Pin number assignments
const int DF_MODE = 2;
const int pin_A0 =  20;
const int pin_A1 =  21;
long interval = 483; // switching delay used to set frequency (ms) 483

void setup() {
// set pins to output
pinMode(DF_MODE, INPUT);
pinMode(pin_A0, OUTPUT);
pinMode(pin_A1, OUTPUT);

//set initial pin states
//digitalWrite(DF_MODE, HIGH);
}

void loop()
{
//Cycle through each pin progressively with delay between
//reference pin only switches every 2 cycles for 50% 500Hz wave

//State1 (0,0)
//Serial.println("State1 (0, 0)");
digitalWrite(pin_A0, LOW);
digitalWrite(pin_A1, LOW);
delayMicroseconds(interval);

//State2 (1,0)
//Serial.println("State2 (1, 0)");
digitalWrite(pin_A0, HIGH);
digitalWrite(pin_A1, LOW);
delayMicroseconds(interval);

//State3 (0,1)
//Serial.println("State3 (0, 1)");
digitalWrite(pin_A0, LOW);
digitalWrite(pin_A1, HIGH);
delayMicroseconds(interval);

//State4 (1,1)
//Serial.println("State4 (1, 1)");
digitalWrite(pin_A0, HIGH);
digitalWrite(pin_A1, HIGH);
delayMicroseconds(interval);}
