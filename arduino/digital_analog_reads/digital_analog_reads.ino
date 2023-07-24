// digital_analog_reads
#define pot_pin 15  // Defining where the pins are connected
#define button_pin 2
#define yellow_led 22
#define red_led 23

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 bits per second
  pinMode(pot_pin, INPUT);  // Pin assignments for all the GPIOs used
  pinMode(button_pin, INPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(red_led, OUTPUT);
}

void loop() {
  if(digitalRead(button_pin) == 1)  // Set the LED state to whatever is the button state
    digitalWrite(red_led, HIGH);
  else
    digitalWrite(red_led, LOW);
  
  int pot_value = analogRead(pot_pin);  // This contains our raw analog value. It ranges from (0,4095), 12-bits
  
  // The analogWrite function takes values in the range (0,255), 8-bits. Hence we have to tranform the raw data
  // The syntax of the map function is,
  // mapped_value = map(input, input_lower_bound, input_upper_bound, output_lower_bound, output_upper_bound)
  int y_led_brightness = map(pot_value, 0, 4095, 0, 255);
  
  analogWrite(yellow_led, y_led_brightness);  // We output the mapped value to the pin

  Serial.print("Raw potentiometer data: "); // Print some useful information
  Serial.print(pot_value);
  Serial.print("\t\t");
  Serial.print("Mapped potentiometer data: ");
  Serial.print(y_led_brightness);
  Serial.print("\t\t");
  Serial.print("Button state: ");
  Serial.println(digitalRead(button_pin));

  delay(100); // We don't want to flood the computer with messages
}
