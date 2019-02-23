//////////////////////////////////////////////////////////////////
//©2011 bildr
//Released under the MIT License - Please reuse change and share
//Reads the keys pressed on a keypad 
//Thanks to Alexander Brevig for his original keypad code.
/////////////////////////////////////////////////////////////////

#include   //needs to be in the library folder (Arduino/Libraries)

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','4','7','*'},
  {'2','5','8','0'},
  {'3','6','9','#'},
  {'A','B','C','D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600); //initialise the serial port (9600 baud)
}

void loop(){
  char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.println(key); //print to serial the key that has been pressed
  }
}
