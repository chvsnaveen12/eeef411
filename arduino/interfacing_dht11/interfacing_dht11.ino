// interfacing_dht11
#include <DHT11.h>

DHT11 dht11(23);  // Create an instance of the DHT11 class and set the pin to 23.

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud.
}

void loop() {
  float temperature = dht11.readTemperature();  // Read the temperature from the sensor.

  // If the temperature reading was successful, print it to the serial monitor.
  if (temperature != -1) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
  }
  // If the temperature reading failed, print an error message.
  else{
    Serial.println("Error reading data");
  }
  // Wait for a second before the next reading.
  delay(1000);
}
