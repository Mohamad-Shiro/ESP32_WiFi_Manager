#include <Arduino.h>
#include <WiFi.h>
#include <WiFi_Manager.h>

#define SERIAL_BAUD 115200

WiFiManager Scanner;

void setup() {
    Serial.begin(SERIAL_BAUD);
    WiFiClass::mode(WIFI_STA);
    Serial.println("WiFi established.");

    // List available networks
    // take user input
    // make decision
    Scanner.start();
}

void loop() {
    if (!Scanner.connection) {
        // Check user input
        // if user input to connect call initializeConnection()
        Serial.println("U have not connected to a network yet!. (connect / skip)");
        if (Scanner.takeInput() == "connect") Scanner.start();

    } else {
        // Should be connected -> if disconnected prompt user and wait for decision
        if (WiFiClass::status() != WL_CONNECTED) {
            Serial.println("WiFi disconnected. reconnect? y/n:");

            if (Scanner.takeInput() == "y")
                Scanner.start();
            else
                Scanner.connection = false;
        }
    }

    Serial.println("Loop entered: (disconnect / reconnect / rescan)");
    String userInput = Scanner.takeInput();

    if (userInput == "disconnect") {
        WiFi.disconnect();
        Serial.println("Disconnecting...");
        delay(100);
        Scanner.connectionHandler(100);
    } else if (userInput == "reconnect") {
        WiFi.reconnect();
        Serial.println("reconnecting...");
        Scanner.connectionHandler(2000);
    } else {
        Scanner.start();
    }

    // Rest of code
    delay(5000);
}
