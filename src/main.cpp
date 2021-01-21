#include <Arduino.h>
#include <led.h> 

led led_body;

void setup() {
  led_body.init();
}

void loop() {
  led_body.body();
}