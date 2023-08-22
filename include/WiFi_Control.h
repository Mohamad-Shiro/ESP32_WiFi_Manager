bool connection = false;

void connect_at_indx(int);
int search_networks(String, int);
String take_input();
int str_to_int(String number);
void list_networks(int);
void init_conn();


void init_conn() {
    String curr_msg = "";

    Serial.println("Scanning...");
    int networks = WiFi.scanNetworks();
    
    bool quit = false;
    while (!quit) {
        if (networks == 0) {
            Serial.println("No networks in range! rescan? y/n");
            // Wait for user input
            curr_msg = take_input();

            while (1) {
                curr_msg = take_input();
                if (curr_msg != "y" && curr_msg != "n") {
                    Serial.println("Please enter valid input: y/n");
                    curr_msg = "";
                } else {
                    break;
                }
            }
            // Check user decision
            // If user input "n" quit connection function. (break main loop)
            // If "y" rescan
            if (curr_msg == "n") quit = true;

        } else {
            list_networks(networks);
            // Enter the number of target network
            // or network name prefixed by ":". (enter "abort" to quit)
            Serial.println("Enter the number of target network");
            Serial.println("or network name prefixed by \":\". (enter \"abort\" to quit)");
            
            while (1) {
                curr_msg = take_input();
                curr_msg.remove(curr_msg.length()-1, curr_msg.length());

                if (curr_msg == "abort") {
                    Serial.println("Aborted");
                    quit = true;
                    break;
                }

                if (curr_msg[0] == ':') {
                    // Search by name
                    curr_msg.remove(0, 1);
                    int indx = search_networks(curr_msg, networks); 
                    if (indx != -1) {
                        connect_at_indx(indx);
                        quit = true;
                        break;
                    } else {
                        Serial.println("Invalid network name, please try again.");
                    }
                    
                } else {
                    // Search by number
                    int indx = str_to_int(curr_msg);
                    if (indx <= networks) {
                        connect_at_indx(indx-1);
                        quit = true;
                        break;
                    } else {
                        Serial.println("Invalid network number, please try again.");
                    }
                }
            }
        }
    }
    
    Serial.println("");
}


void list_networks(int n) {
    Serial.print(n);
    Serial.println(" networks found. listing..");
    for (int i = 0; i < n; ++i) {
        // Print SSID and RSSI for each network found
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");
        Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
    }
}

int str_to_int(String number) {
    int x = 0;
    for (int i = 0; i < number.length(); i++) {
        int tmp = number[i] - '0';
        x = x*10 + tmp;
    }
    return x;
}


String take_input() {
    while (1) {
        if (Serial.available()) {
            String msg = Serial.readString();

            if (!msg.isEmpty()) {
                return msg;
                break;
            } else Serial.println("Please enter non-empty input..");
        }
        delay(100);
    }
}

int search_networks(String name, int n) {
    for (int i = 0; i < n; ++i) {
        if (name == WiFi.SSID(i)) {
            return i;
        }
    }
    return -1;
}

void connect_at_indx(int indx) {
    String name = WiFi.SSID(indx);

    if (WiFi.encryptionType(indx) == WIFI_AUTH_OPEN) {
        Serial.print("Connecting to WiFi ");
        Serial.print(name);
        Serial.println("...");
        WiFi.begin(name, "");

    } else {
        Serial.print("Enter password for ");
        Serial.print(name);
        Serial.println(":");

        String password = take_input();

        Serial.print("Connecting to WiFi ");
        Serial.print(name);
        Serial.println("...");
        WiFi.begin(name, password);
    }
    
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    Serial.println(" Connected!");
    connection = true;
}
