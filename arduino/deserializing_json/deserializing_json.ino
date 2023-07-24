// deserializing_json
#include <Arduino.h>  // Include the necessary libraries
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

String ssid = "YOUR_SSID";  // Modify them.
String password = "YOUR_PASSWORD";

String serverName = "https://official-joke-api.appspot.com/random_joke";  // The API we will be hitting

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

    if (httpResponseCode > 0) { // If the request was successful
      DynamicJsonDocument doc(512); // Initialize the JSON document
      deserializeJson(doc, http.getString()); // Parse the raw data
      Serial.print("type: ");
      Serial.println(doc["type"].as<String>()); // Print the value associated with the key "type" as a String object 
      Serial.print("setup: ");
      Serial.println(doc["setup"].as<String>());
      Serial.print("punchline: ");
      Serial.println(doc["punchline"].as<String>());
      Serial.print("id: ");
      Serial.println(doc["id"].as<int>());
      Serial.println("");

    } else {  // The request wasn't successful
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      Serial.println("");
    }

    http.end();  // Destroy the http object

  } else {
    Serial.println("WiFi Disconnected");
  }
  delay(5000);  // Make a request every 5 seconds
}