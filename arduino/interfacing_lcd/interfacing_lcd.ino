// interfacing_lcd
#include <Wire.h>  // Include the necessary libraries
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

int number = 0; // Test variable

void setup() {
  lcd.init();           // Initialize the lcd
  lcd.backlight();      // Turn on the backlight
  lcd.setCursor(2, 0);  // Set the cursor position to 4th column and 1st row
  lcd.print("Hello, world!"); // Print a Hello World message
  delay(2000);  // Wait for two seconds before entering the main loop
}

void loop() {
  lcd.clear();  // Clear the LCD
  lcd.setCursor(3, 0);
  lcd.print("Number: ");
  lcd.print(number);  // Print the number
  lcd.setCursor(0, 1);
  lcd.print("Unit's place: ");
  lcd.print(number%10); // Print its unit's place

  number++;
  delay(1000);  // Wait a second before looping
}

