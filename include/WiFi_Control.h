bool connection = false;

wl_status_t checkConnectionTimeout(int timeOut);
void connectionHandler(int);
void connectToNetwork(int index);
int searchNetworks(const String& name, int numNetworks);
void listNetworks(int numNetworks);
int stringToInt(const String& str);
String takeInput();
void initializeConnection();

void initializeConnection() {
    String userInput;

    while (true) {
        Serial.println("Scanning...");
        int numNetworks = WiFi.scanNetworks();

        if (numNetworks == 0) {
            Serial.println("No networks in range! Do you want to rescan? (y/n)");
            userInput = takeInput();
            if (userInput == "n") {
                break;
            }
        } else {
            listNetworks(numNetworks);
            Serial.println("Enter the number or name (prefixed with \":\") of the target network (enter \"abort\" to quit):");
            userInput = takeInput();

            if (userInput == "abort") {
                Serial.println("Aborted");
                break;
            }

            if (userInput[0] == ':') {
                String networkName = userInput.substring(1);
                int index = searchNetworks(networkName, numNetworks);
                if (index != -1) {
                    connectToNetwork(index);
                    break;
                } else {
                    Serial.println("Invalid network name, please try again.");
                }
            } else {
                int index = userInput.toInt();
                if (index >= 1 && index <= numNetworks) {
                    connectToNetwork(index - 1);
                    break;
                } else {
                    Serial.println("Invalid network number, please try again.");
                }
            }
        }
    }
}

void listNetworks(int numNetworks) {
    Serial.print(numNetworks);
    Serial.println(" networks found. Listing...");
    
    for (int i = 0; i < numNetworks; ++i) {
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");
        Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
    }
}


String takeInput() {
    while (true) {
        if (Serial.available()) {
            String msg = Serial.readString();
            msg.trim();

            if (!msg.isEmpty()) {
                return msg;
            } else {
                Serial.println("Please enter non-empty input.");
            }
        }
        delay(100);
    }
}

int searchNetworks(const String& name, int numNetworks) {
    for (int i = 0; i < numNetworks; ++i) {
        if (name == WiFi.SSID(i)) {
            return i;
        }
    }
    return -1;
}

void connectToNetwork(int index) {
    String networkName = WiFi.SSID(index);

    if (WiFi.encryptionType(index) == WIFI_AUTH_OPEN) {
        Serial.print("Connecting to ");
        Serial.print(networkName);
        Serial.println("...");

        WiFi.begin(networkName);
        connectionHandler(5000);

    } else {
        Serial.print("Enter password for ");
        Serial.print(networkName);
        Serial.println(":");

        String password = takeInput();
        
        Serial.print("Connecting to ");
        Serial.print(networkName);
        Serial.println("...");
        
        WiFi.begin(networkName, password);
        connectionHandler(5000);
    }
}

void connectionHandler(int timeOut = 10000) {
    wl_status_t connectionStatus = checkConnectionTimeout(timeOut);  // Adjust timeout as needed

    switch (connectionStatus) {
        case WL_CONNECTED:
            Serial.println("Connected to Wi-Fi.");
            connection = true;
            break;

        case WL_NO_SSID_AVAIL:
            Serial.println("No such network available. Would you like to rescan? (y/n)");
            if (takeInput() == "y") {
                initializeConnection();
            } else {
                Serial.println("Aborted.");
            }
            break;

        case WL_CONNECT_FAILED:
            Serial.println("Incorrect credentials. Would you like to retry? (y/n)");

            if (takeInput() == "y") initializeConnection();
            else Serial.println("Aborted.");
            break;
        case WL_CONNECTION_LOST:
            Serial.println("Connection lost. Would you like to retry? (y/n)");

            if (takeInput() == "y") initializeConnection();
            else Serial.println("Aborted.");
            break;

        case WL_DISCONNECTED:
            Serial.println("Disconnected from Wi-Fi.");
            connection = false;
            break;

        default:
            break;
    }
}

wl_status_t checkConnectionTimeout(int timeOut) {
    int initTime = millis();
    int currTime = initTime;
    wl_status_t connectionStatus = WiFi.status();

    while (connectionStatus != WL_CONNECTED && (currTime - initTime < timeOut)) {
        delay(100);
        Serial.print(".");
        currTime = millis();
        connectionStatus = WiFi.status();
    }

    return connectionStatus;
}
