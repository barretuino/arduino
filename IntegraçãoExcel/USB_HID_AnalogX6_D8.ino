// 20121210 Runs on UNO-clone strip board using 328P-PU
// 20121214 Runs on Nano commercial clone
// UNO Profile:  Binary sketch size: 8,260 bytes (of a 32,256 byte maximum)
// Nano Profile: Binary sketch size: 8,260 bytes (of a 30,720 byte maximum)

// When freeram function is uncommented: FREE RAM 1506

#include "UsbKeyboard.h"
#include <avr/pgmspace.h>

// #define BUTTON_PIN 10

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

String sOut;

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

void delayMs(unsigned int ms) {    // Safe delay helper function
  for (int i = 0; i < ms; i++) {
    delayMicroseconds(1000);
  }
}


void setup() {
  // pinMode(BUTTON_PIN, INPUT);
  // digitalWrite(BUTTON_PIN, HIGH);

  // Disable timer0 since it can mess with the USB timing. Note that
  // this means some functions such as delay() will no longer work.
  TIMSK0&=!(1<<TOIE0);
  // Clear interrupts while performing time-critical operations
  cli();
  // Force re-enumeration so the host will detect us
  usbDeviceDisconnect();
  delayMs(250);
  usbDeviceConnect();

  // Set interrupts again
  sei();

  pinMode(3, INPUT);      //  sets the digital pin 3 as input
  pinMode(6, INPUT);      //  sets the digital pin 6 as input
  pinMode(7, INPUT);      //  sets the digital pin 7 as input
  pinMode(8, INPUT);      //  sets the digital pin 8 as input
  pinMode(9, INPUT);      //  sets the digital pin 9 as input
  pinMode(10, INPUT);      // sets the digital pin 10 as input
  pinMode(11, INPUT);      // sets the digital pin 11 as input
  pinMode(12, INPUT);      // sets the digital pin 12 as input

  for (int i = 0; i < 500; i++){            // 10 second delay in lieu of using Button press on pin 10
    digitalWrite(13, !digitalRead(13));
    // while (digitalRead(BUTTON_PIN) != 0)
     UsbKeyboard.update();
     delayMs(20);
   }

  // Tell them who we are...
  sOut = "SIMPLE HID DATA LOGGER USING VUSB WWW.OBDEV.AT";
  KeyStrokeAlpNum(sOut);
  sOut = "ARDUINO PORT BY RANCIDBACON.COM";
  KeyStrokeAlpNum(sOut);
  sOut = "UNO 328P EXAMPLE - RAY BURNETTE C20121210";
  KeyStrokeAlpNum(sOut);
  UsbKeyboard.sendKeyStroke(KEY_ENTER);
  UsbKeyboard.sendKeyStroke(KEY_ENTER); 
}


void loop() {
    digitalWrite(13, !digitalRead(13));    // flash LED
    UsbKeyboard.update();
    
    for (int i = 0; i < 6; i++){
      // read the analog in value:
      sensorValue = analogRead( i );
      // Label the value
      sOut = "ANALOG";
      // String the characters together
      sOut.concat(String(i));
      sOut.concat(" ");
      sOut.concat(String(sensorValue));
      // spool the combined strings
      KeyStrokeAlpNum(sOut);
    }

    sOut = "DIGITAL ";
    if (digitalRead(3) == HIGH){
      sOut.concat("3H ");
    } else {
        sOut.concat("3L ");
    }
    if (digitalRead(6) == HIGH){
      sOut.concat("6H ");
    } else {
        sOut.concat("6L ");
    }
    if (digitalRead(7) == HIGH){
      sOut.concat("7H ");
    } else {
        sOut.concat("7L ");
    }
    if (digitalRead(8) == HIGH){
      sOut.concat("8H ");
    } else {
        sOut.concat("8L ");
    }
    if (digitalRead(9) == HIGH){
      sOut.concat("9H ");
    } else {
        sOut.concat("9L ");
    }
    if (digitalRead(10) == HIGH){
      sOut.concat("10H ");
    } else {
        sOut.concat("10L ");
    }
    if (digitalRead(11) == HIGH){
      sOut.concat("11H ");
    } else {
        sOut.concat("11L ");
    }
    if (digitalRead(12) == HIGH){
      sOut.concat("12H");
    } else {
        sOut.concat("12L");
    }

    KeyStrokeAlpNum(sOut);
    UsbKeyboard.sendKeyStroke(KEY_ENTER);
    // sOut = "FREE RAM ";              // Uncomment next 4 lines to check for memory leaks
    // sOut.concat(String(freeRam()));
    // KeyStrokeAlpNum(sOut);
    // UsbKeyboard.sendKeyStroke(KEY_ENTER);
    delayMs(5000);    // Interrupt safe since V-USB utilizes interrupt
}


void KeyStrokeAlpNum(String Sc){
    int sPoint = Sc.length();          // Pointer to end-of-String (inc. null)
    for (int x = 0; x < sPoint; x++){
      int y = x + 1;
      if (Sc.substring(x, y) == "H"){  // substring single character: y = x+1
          UsbKeyboard.sendKeyStroke(KEY_H, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "L"){
          UsbKeyboard.sendKeyStroke(KEY_L, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == " "){
          UsbKeyboard.sendKeyStroke(KEY_SPACE);
          }
       else if (Sc.substring(x, y) == "1"){
          UsbKeyboard.sendKeyStroke(KEY_1);
          }
       else if (Sc.substring(x, y) == "2"){
          UsbKeyboard.sendKeyStroke(KEY_2);
          }
       else if (Sc.substring(x, y) == "3"){
          UsbKeyboard.sendKeyStroke(KEY_3);
          }
       else if (Sc.substring(x, y) == "4"){
          UsbKeyboard.sendKeyStroke(KEY_4);
          }
       else if (Sc.substring(x, y) == "5"){
          UsbKeyboard.sendKeyStroke(KEY_5);
          }
       else if (Sc.substring(x, y) == "6"){
          UsbKeyboard.sendKeyStroke(KEY_6);
          }
       else if (Sc.substring(x, y) == "7"){
          UsbKeyboard.sendKeyStroke(KEY_7);
          }
       else if (Sc.substring(x, y) == "8"){
          UsbKeyboard.sendKeyStroke(KEY_8);
          }
       else if (Sc.substring(x, y) == "9"){
          UsbKeyboard.sendKeyStroke(KEY_9);
          }
       else if (Sc.substring(x, y) == "0"){
          UsbKeyboard.sendKeyStroke(KEY_0);
          }
       else if (Sc.substring(x, y) == "."){
          UsbKeyboard.sendKeyStroke(55);
          }
       else if (Sc.substring(x, y) == "-"){
          UsbKeyboard.sendKeyStroke(45);
          }
       else if (Sc.substring(x, y) == "A"){
          UsbKeyboard.sendKeyStroke(KEY_A, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "B"){
          UsbKeyboard.sendKeyStroke(KEY_B, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "C"){
          UsbKeyboard.sendKeyStroke(KEY_C, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "D"){
          UsbKeyboard.sendKeyStroke(KEY_D, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "E"){
          UsbKeyboard.sendKeyStroke(KEY_E, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "F"){
          UsbKeyboard.sendKeyStroke(KEY_F, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "G"){
          UsbKeyboard.sendKeyStroke(KEY_G, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "I"){
          UsbKeyboard.sendKeyStroke(KEY_I, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "J"){
          UsbKeyboard.sendKeyStroke(KEY_J, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "K"){
          UsbKeyboard.sendKeyStroke(KEY_K, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "M"){
          UsbKeyboard.sendKeyStroke(KEY_M, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "N"){
          UsbKeyboard.sendKeyStroke(KEY_N, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "O"){
          UsbKeyboard.sendKeyStroke(KEY_O, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "P"){
          UsbKeyboard.sendKeyStroke(KEY_P, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "Q"){
          UsbKeyboard.sendKeyStroke(KEY_Q, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "R"){
          UsbKeyboard.sendKeyStroke(KEY_R, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "S"){
          UsbKeyboard.sendKeyStroke(KEY_S, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "T"){
          UsbKeyboard.sendKeyStroke(KEY_T, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "U"){
          UsbKeyboard.sendKeyStroke(KEY_U, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "V"){
          UsbKeyboard.sendKeyStroke(KEY_V, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "W"){
          UsbKeyboard.sendKeyStroke(KEY_W, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "X"){
          UsbKeyboard.sendKeyStroke(KEY_X, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "Y"){
          UsbKeyboard.sendKeyStroke(KEY_Y, MOD_SHIFT_LEFT);
          }
       else if (Sc.substring(x, y) == "Z"){
          UsbKeyboard.sendKeyStroke(KEY_Z, MOD_SHIFT_LEFT);
          }
      }
      UsbKeyboard.sendKeyStroke(KEY_ENTER);
      // Return
}

/*  Additional translations

          45 -
          46 =
          47 [
          48 ]
          49 \
          50 \
          51 ;
          52 '
          53 `
          54 ,
          55 .
          56 /
          
          84 /
          85 *
          86 -
          87 +
*/

