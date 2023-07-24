// sending_information
#include <HTTPClient.h>  // Include the necessary libraries
#include <Arduino.h>
#include <WiFi.h>
#include <DHT11.h>

String ssid = "YOUR_SSID";  // Modify them.
String password = "YOUR_PASSWORD";
String url = "http://SERVER_IP:SERVER_PORT/esp/NODE_ID/";

DHT11 dht11(23);  // Create an instance of the DHT11 class and set the pin to 23.

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 baud.

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
  // If the temperature reading wasn't successful, print it to the serial monitor.
  // And keep trying until we get a valid reading.
  float temperature = dht11.readTemperature();
  while (temperature < 0) {
    float temperature = dht11.readTemperature();
    Serial.println("No temp");
    delay(100);
  }

  // Convert the float temperature to a String object with 4 decimal places
  String temp_str = String(temperature, 4);
  Serial.println(url + temp_str);

  // If we are connected, send the information to the server.
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;             // Initialize a http object
    http.begin(url + temp_str);  // Send the HTTP GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();  // Print the received raw data
      Serial.println(payload);
      Serial.println();
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      Serial.println("");
    }
    http.end();  //Close connection
  } else {
    Serial.println("WiFi Disconnected");
  }
  delay(1000);
}