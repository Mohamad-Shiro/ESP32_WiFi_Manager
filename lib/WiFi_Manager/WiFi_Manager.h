#include <Arduino.h>
#include <WiFi.h>

class WiFiManager {
   public:
    bool connection;
    WiFiManager();

    /**
     * @public
     * Initializes the Wi-Fi connection process by scanning for available networks and waits user interaction.
     *
     * User can choose to abort at any time.
     *
     * User can choose the desired network either by its number or name prefixed by ":".
     *
     * It handles incorrect network number, name and password prompting the user to try again.
     *
     */
    void start();

    /**
     * @public
     * Connect to a known network Directly
     *
     * @param ssid Name of network
     * @param password Password of network
     */
    void connectToNetwork(char * ssid, char * password);

    /**
     * @public
     * Captures user input from the Serial interface and trims leading/trailing spaces.
     *
     * @return Cleaned input string from the user.
     */
    String takeInput();

    /**
     * @public
     * Handles various Wi-Fi connection states and prompts user interactions.
     *
     * @param timeOut (Optional) Timeout in milliseconds for the connection (default is 10 seconds).
     */
    void connectionHandler(int timeOut);

   private:
    static const int DEFAULT_CONNECTION_HANDLER_TIME_OUT = 10000;

    /**
     * @private
     * Checks the Wi-Fi connection status within a specified timeout period.
     *
     * @param timeOut Timeout in milliseconds for checking the connection.
     * @return Wi-Fi connection status (WL_CONNECTED, WL_NO_SSID_AVAIL, WL_CONNECT_FAILED,
     *         WL_CONNECTION_LOST, or WL_DISCONNECTED).
     */
    wl_status_t checkConnectionTimeout(int timeOut);

    /**
     * @private
     * Attempts to connect to a Wi-Fi network at the given index in the scan list.
     * Handles both open and password-protected networks and invokes 'connectionHandler'.
     *
     * @param index Index of the network in the scan list to connect to.
     */
    void connectToNetwork(int index);

    /**
     * @private
     * Searches for a Wi-Fi network by its name in the scanned networks list.
     *
     * @param name The name of the Wi-Fi network to search for.
     * @param numNetworks Number of networks in the scanned list.
     * @return Index of the network if found, otherwise -1.
     */
    int searchNetworks(const String& name, int numNetworks);

    /**
     * @private
     * Lists the scanned Wi-Fi networks, displaying their names signal strength and encryption status.
     *
     * @param numNetworks Number of networks in the scanned list.
     */
    void listNetworks(int numNetworks);
};