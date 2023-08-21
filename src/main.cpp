#include <Arduino.h>

#define SERIAL_BAUD 115200


void setup() {
    Serial.begin(SERIAL_BAUD);
    Serial.println("Hello World!");
}

void loop() {
    
}