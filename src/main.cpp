#include <Arduino.h>
#include <WiFi.h>

#include <WiFi_Control.h>

#define SERIAL_BAUD 115200



void setup() {
    Serial.begin(SERIAL_BAUD);
    WiFi.mode(WIFI_STA);
    Serial.println("WiFi established.");

    // List availiable networks
    // take user input
    // make decision
    initializeConnection();
}

void loop() {
    if (!connection) {
        // Check user input
        // if user input to connect call initializeConnection()
        Serial.println("U have not connected to a network yet!. (connect / skip)");
        if (takeInput() == "connect") initializeConnection();

    } else {
        // Should be connected -> if disconnected prompt user and wait for decision
        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("WiFi disconnected. reconnect? y/n:");

            if (takeInput() == "y") initializeConnection();
            else connection = false;
        }
    }

    
    Serial.println("Loop entered: (disconnect / reconnect / rescan)");
    String userInput = takeInput();
    
    if (userInput == "disconnect") {
        WiFi.disconnect();
        Serial.println("Disconnecting...");
        delay(100);
        connectionHandler(100);
    } else if (userInput == "reconnect") {
        WiFi.reconnect();
        Serial.println("reconnecting...");
        connectionHandler(2000);
    } else {
        initializeConnection();
    }

    // Rest of code
    delay(5000);
}
