// btc_usd_tracker
#include <Arduino.h>  // Include the necessary libraries
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

String ssid = "YOUR_SSID";  // Modify them.
String password = "YOUR_PASSWORD";

String serverName = "https://api.coindesk.com/v1/bpi/currentprice.json";  // The API we will be hitting

byte GBP[8] = {  // Defining the bitmap for the GBP character
	0b00110,
	0b01001,
	0b01000,
	0b11110,
	0b01000,
	0b01000,
	0b11111,
	0b00000
};

void setup() {
  lcd.init();            // Initialize the lcd
  lcd.backlight();       // Turn on the backlight
  lcd.createChar(0, GBP);  // Add the GBP character
  Serial.begin(115200);  // Initialize serial communication at 115200 baud

  WiFi.begin(ssid, password);  // Connect to the WiFi with given SSID and password
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {  // Wait till we are successfully connected
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected");
  Serial.println("");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {  //Check WiFi connection status

    HTTPClient http;         // Initialize a http object
    http.begin(serverName);  // Send the HTTP GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {                // If the request was successful
      DynamicJsonDocument doc(2048);           // Initialize the JSON document
      deserializeJson(doc, http.getString());  // Parse the raw data

      // Get the value associated with the key "bpi->USD->rate" as a String object
      String rate = doc["bpi"]["USD"]["rate"].as<String>();

      // We don't want to display the number upto 4 decimal places. We only want 2 decimal places.
      rate.remove(rate.length() - 2, 2);  // Remove the last two characters from the rate.

      // Print the data to the Serial Monitor
      Serial.println("BTC/USD Rate: ");
      Serial.print("Rate: ");
      Serial.print("$");
      Serial.println(rate);
      Serial.println("");

      lcd.clear();          // Clear the LCD
      lcd.setCursor(0, 0);  // Set the cursor to the first character of first line
      lcd.print("BTC/USD Rate: ");
      lcd.setCursor(0, 1);  // Set the cursor to the first character of second line
      lcd.print("$");
      lcd.print(rate);  // Print the formatted rate value
    } else {            // The request wasn't successful
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      Serial.println("");
    }

    http.end();  // Destroy the http object

  } else {
    Serial.println("WiFi Disconnected");
  }
  delay(60000);  // Make a request and update the lcd every minute
}