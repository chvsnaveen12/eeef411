// wifi_api
#include <Arduino.h>  // Include the necessary libraries
#include <WiFi.h>
#include <HTTPClient.h>

String ssid = "YOUR_SSID";  // Modify them.
String password = "YOUR_PASSWORD";

String serverName = "https://catfact.ninja/fact";  // The API we will be hitting

void setup() {
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

    HTTPClient http;  // Initialize a http object
    http.begin(serverName);  // Send the HTTP GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();  // Print the received raw data
      Serial.println(payload);
      Serial.println("");
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      Serial.println("");
    }

    http.end();  // End to destroy the http object

  } 
  delay(5000);  // Make a request every 5 seconds
}