
/*
Arduino Data Logger 1.0
created March 13th 2014 by Roberto Valgolio
last modified 
this example code is in the public domain
any feedback will be appreciated, please write to roberto.valgolio@gmail.com

This sketch sends over serial csv messages with info that can be represented by Arduino Excel Commander (Excel file with VBA code) by the same author.
You can also use a terminal like Putty to capture the output and save it in a text file for other uses.
*/

int i;       // index

void setup(){
  
  Serial.begin(9600);
  //Serial.begin(115200);
  Serial.println("hello from Arduino");
}

void loop(){
  
  // the output format to Excel is:
  // XLS,CellName,Index,Value
  // where:
  //   'XLS' is a constant keyword for messages to Excel
  //   'CellName' is a keyword that specifies the cells(s) name where info will be allocated in
  //   'Index specifies the item (forced to zero for simple variables)
  //   'Value' is the info value 
  // messages are \n terminated
  // use Arduino Excel Logger of the same author for messages reading and info real time representing
  
  // example 1
  // the following info will be placed in a cell VAR1 named
  Serial.print("XLS,VAR1,");
  Serial.print("0"); // while we are sending a simple variable index is forced to zero
  Serial.print(",");
  Serial.print(analogRead(0)); // only for example, put here your variable
  Serial.print("\n");

  // example 2
  // the following info will be placed in a cell VAR2 named
  Serial.print("XLS,VAR2,");
  Serial.print("0"); // while we are sending a simple variable index is forced to zero
  Serial.print(",");
  Serial.print(analogRead(1)); // only for example, put here your variable
  Serial.print("\n");
  
  // example 3
  // the following info will be placed in a cell VAR3 named
  Serial.print("XLS,VAR3,");
  Serial.print("0"); // while we are sending a simple variable index is forced to zero
  Serial.print(",");
  Serial.print(analogRead(2)); // only for example, put here your variable
  Serial.print("\n");

  // example 4
  // the following info will be placed at i position of a cell group named ARR1
  Serial.print("XLS,ARR1,");
  Serial.print(i); // only for example, put here your index
  Serial.print(",");
  Serial.print(random(0, 100)); // only for example, put here your variable
  Serial.print("\n");

  delay(1000);
  
  i++;
  
}

