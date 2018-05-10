/*
This code will calculate the CPM of your counter based on a 5V Input (Falling) on PIN 0 and send it to the PC through Serial (9600) baud.
PROTECT YOUR ARDUINO! Please consider using a pullup resistor on the input Pin. Check the specs of your counter for the max. output current.

Lucas Koch, May 2018
*/
#include <SPI.h>
#define LOG_PERIOD 15000  //log period
#define MAX_PERIOD 60000  //max period
int counts;
unsigned long cpm;
int multiplier;
unsigned long previousMillis;


void setup() {
  // put your setup code here, to run once:
  counts = 0;
  cpm = 0;
  multiplier = MAX_PERIOD/LOG_PERIOD;
  Serial.begin(9600);  //9600 baud
  attachInterrupt(0, Pulse, FALLING); //Select your pin, attach interrupt Pulse()
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > LOG_PERIOD){  //Execute code periodically every <LOG_PERIOD> ms
    previousMillis = currentMillis;
    cpm = counts * multiplier;
    Serial.print(cpm);
    Serial.write(' ');
    counts = 0;
  }
}

void Pulse(){
  counts++;  //Add one count
}

