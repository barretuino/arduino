/*
 Demonstrates the use a 16x2 LCD display from dx.com 
 */
// include the library code:
#include <Time.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // pins for the DX.com lcd board http://dx.com/p/lcd-keypad-shield-for-arduino-duemilanove-lcd-1602-118059
//lcd(12, 11, 5, 4, 3, 2); // original arduion example pins
byte keyvalue;
int LastSecond=0;
boolean state0=LOW;
boolean state1=LOW;
boolean state2=LOW;
boolean state3=LOW;
boolean state10=HIGH;
boolean state11=LOW;
boolean state12=LOW;
boolean state13=LOW;
int barChar=90;
void setup() {
  pinMode(0, OUTPUT);  // data IO
  pinMode(1, OUTPUT);  // data IO
  pinMode(2, OUTPUT);  // data IO
  pinMode(3, OUTPUT);  // data IO
  pinMode(13, OUTPUT);  // onboard led
  pinMode(17, OUTPUT);  // onboard led2
  pinMode(11, OUTPUT);  // Pinned on ICSP of LCD Keypad
  pinMode(12, OUTPUT);  // Pinned on ICSP of LCD Keypad
  pinMode(13, OUTPUT);  // Pinned on ICSP of LCD Keypad
  pinMode(10, OUTPUT); // LCD Keypad Shield BACKlight
  digitalWrite(10, state10);

  lcd.begin(16, 2);  // set up the LCD's number of columns and rows: 
  setTime(6,22,11,29,06,2013);  // setTime(hour,minute,second,day,month,year)
}
void loop() {
  lcd.noCursor();
  showtime(); // show time
  delay(10);
  keypressed(); // show value for keys
  showtime(); // show time
  delay(10);
  keypressed(); // show value for keys
  if (LastSecond!=second()) {
     // MoistureTest();
    LastSecond=second();  
  }
  digitalWrite(13, state13);
  if(state13==LOW) { state13=HIGH; }else{state13=LOW;}

}
void keypressed(){
  analogRead(A0);
  int value = analogRead(A0)/12;
  if(value<70){keyvalue=60;}else{keyvalue=80; return;}
  if(value<50)keyvalue=39;
  if(value<31)keyvalue=25;
  if(value<16)keyvalue=10;
  if(value<5)keyvalue=0;
  lcd.setCursor(15,1); // set cusor position to row 1, col 1
  //lcd.print(keyvalue);   // value on A0
  
  if(keyvalue==85) return;
  if(keyvalue==10) {
    lcd.print("^");
  }  
  if(keyvalue==25) {
    lcd.print("V");
  }  
  if(keyvalue==39) {
    lcd.print("<");
    barChar--;
  }  
  if(keyvalue==0) {
    lcd.print(">");
    barChar++;
  }  
  if(keyvalue==60) {
    lcd.print("*");
    if(state10==LOW) { state10=HIGH; }else{state10=LOW;}
    digitalWrite(10, state10);
    delay(400);
  }  
  if(keyvalue==25)   {  adjustTime(-62); delay(100);}
  if(keyvalue==10)   {  adjustTime(1); delay(100);}
  showtime();
  delay(90);
  lcd.setCursor(7, 0);  lcd.print(barChar);lcd.print(" ");lcd.print(char(barChar));
  delay(90);
}  

void showtime(){
     // lcd.setCursor(0, 0);  lcd.print(now());
  lcd.setCursor(0, 1);
  if (hour()<10) lcd.print("0");
  lcd.print(hour());
  lcd.print(":");
  if (minute()<10) lcd.print("0");
  lcd.print(minute());
  lcd.print(".");
  if (second()<10) lcd.print("0");
  lcd.cursor();
  lcd.print(second());  lcd.print(" ");
  lcd.setCursor(7, 1);
  delay(50);
}  
