#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Paulo Barreto");
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.clear();
  lcd.print("Barretuino");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("LCD Shield 1602");  
  lcd.setCursor(0, 1); 
  lcd.print("por R$ 25,00");

  delay(2000);
}

