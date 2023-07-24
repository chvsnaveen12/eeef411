// first_program
#define builtin_led 2  // The devkit has a LED connected to GPIO 2

void setup(){
  // The code inside the void setup only runs once, at the beginning
  pinMode (builtin_led, OUTPUT);   // Define builtin_led as a OUTPUT
}
	
void loop(){
  // The code inside the void loop runs indefinitely.
  digitalWrite(builtin_led, HIGH); // Turn on the led
  delay(1000);                     // Wait 1000 milliseconds
  digitalWrite(builtin_led, LOW);  // Turn off the led
  delay(1000);                     // Wait 1000 milliseconds
}