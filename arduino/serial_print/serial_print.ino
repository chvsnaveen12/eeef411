// serial_print
int number;

void setup() {
  number = 0;
  Serial.begin(9600);  // initialize serial communication at 9600 bits per second
}

void loop() {
  number++;
  Serial.print("Hello World! "); // next print would happen in the same line
  Serial.println(number%10); // next print would happen on a new line
  delay(100); // We don't want to flood the PC with messages
}