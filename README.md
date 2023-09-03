# WiFiManager Library Documentation

The `WiFiManager` library provides a convenient way to manage Wi-Fi connections on an ESP32 device. It encapsulates the process of scanning for available networks, connecting to them, and handling connection states.

## Class: `WiFiManager`

### Public Members

- `bool connection`: Represents the connection status. `true` if connected to Wi-Fi, `false` otherwise.

### Constructors

- `WiFiManager()`: Default constructor to initialize the `WiFiManager` class.

### Public Methods

#### [`void start()`](https://github.com/Mohamad-Shiro/ESP32_WiFi_Manager/blob/c9d99e5dd48707facd76805f9bbbee4e80cfe53e/lib/WiFi_Manager/WiFi_Manager.cpp#L5C1-L46C2)

Initializes the Wi-Fi connection process by scanning for available networks and waiting for user interaction.

- The user can choose to abort at any time by entering "abort".
- The user can choose the desired network either by its number or name prefixed by ":".
- Handles incorrect network numbers, names, and passwords by prompting the user to try again.

**Example:**

`WiFiManager wifiManager; wifiManager.start();`

#### [`void connectToNetwork(name, password)`](https://github.com/Mohamad-Shiro/ESP32_WiFi_Manager/blob/e953db1a77c571cc4bf57ab725dfe1f165614291/lib/WiFi_Manager/WiFi_Manager.cpp#L48-L56)

Connects directly to known network.
- `char * ssid` name of network.
- `char * password` password of network.
**Example:**

`WiFiManager wifiManager; wifiManager.connectToNetwork("Network name", "Network password");`

#### [`String takeInput()`](https://github.com/Mohamad-Shiro/ESP32_WiFi_Manager/blob/c9d99e5dd48707facd76805f9bbbee4e80cfe53e/lib/WiFi_Manager/WiFi_Manager.cpp#L63-L77)

Captures user input from the Serial interface and trims leading/trailing spaces.

- Returns a cleaned input string from the user.

**Example:**

`WiFiManager wifiManager; String userInput = wifiManager.takeInput();`

#### [`void connectionHandler(int timeOut)`](https://github.com/Mohamad-Shiro/ESP32_WiFi_Manager/blob/c9d99e5dd48707facd76805f9bbbee4e80cfe53e/lib/WiFi_Manager/WiFi_Manager.cpp#L115-L159)

Handles various Wi-Fi connection states and prompts user interactions.

- `timeOut` (Optional): Timeout in milliseconds for the connection (default is 10 seconds).

**Example:**

`WiFiManager wifiManager; wifiManager.connectionHandler();`

### Usage

1. **Initializing the WiFiManager:**
    
    To begin using the `WiFiManager` library, create an instance of the class:
    
    `WiFiManager wifiManager;`
    
2. **Starting the Wi-Fi Connection Process:**
    
    Use the `start()` method to initiate the Wi-Fi connection process. It scans for available networks and prompts user interactions to choose a network:
    
    `wifiManager.start();`
    
3. **Capturing User Input:**
    
    The `takeInput()` method captures user input from the Serial interface, trimming any leading/trailing spaces:
    
    `String userInput = wifiManager.takeInput();`
    
4. **Handling Connection States:**
    
    The `connectionHandler()` method handles various Wi-Fi connection states and user interactions. You can specify a timeout for the connection attempt:
    
    `wifiManager.connectionHandler();`
