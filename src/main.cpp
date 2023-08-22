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
    init_conn();
}

void loop() {
    if (!connection) {
        // Check user input
        // if user input to connect call init_conn()
        Serial.println("U have not connected to a network yet!. (connect / skip)");
        String msg0 = take_input();
        if (msg0 == "connect") {
          init_conn();
        }
    } else {
        // Should be connected -> if disconnected prompt user and wait for decision
        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("WiFi disconnected. reconnect? y/n:");
            String msg0 = take_input();
            if (msg0 == "y") {
                init_conn();
            } else {
                connection = false;
            }
        }
    }

    
    Serial.println("Loop entered: (disconnect / reconnect / rescan)");
    String msg = take_input();
    Serial.println(msg);
    if (msg == "disconnect") {
        WiFi.disconnect();
        delay(100);
        connection_handler();
    } else if (msg == "reconnect") {
        WiFi.reconnect();
        check_connection_timeout(5000);
        connection_handler();
    } else {
        init_conn();
    }

    // Rest of code
    delay(5000);
}
