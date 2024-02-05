#include <Arduino.h>
#include "pinSetup.h"

#define LED 2

void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop()
{
  digitalWrite(LED, HIGH);
  Serial.println("LED is on");
  delay(1000);
  digitalWrite(LED, LOW);
  Serial.println("LED is off");
  delay(1000);
}