#include <RealTime.h>

Blinker led(13, 500); // pin 13, 500 milliseconds to blink

void setup() {
}

void loop() {
  led.blink();
}
