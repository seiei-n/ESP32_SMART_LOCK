

#include <ESP32Servo.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
 
const int SERVO = 12; // サーボモーターピン
char input;
 
Servo servo;            // サーボクラス


void open(){
  servo.write(90);
  delay(500);
  }
void close(){
  servo.write(180);
  delay(500);
  }
void setup() {
  servo.attach(SERVO);  // サーボモーターの制御ピン設定
  SerialBT.begin(ESP32);
  Serial.begin(115200);
  SerialBT.println("OK!!");
  
}
 
void loop() {
   


  // 受信データがあった時だけ、処理を行う
  if (SerialBT.available()>0){
    input = SerialBT.read();
    if(input == '1'){
      SerialBT.println("Open!");
      open();
      }
    else if (input == '2'){
      SerialBT.println("Close!");
      close();
      }
    }
   else if (Serial.available()>0){
    input = Serial.read();
    if(input == '1'){
      Serial.println("Open!");
      open();
      }
    else if (input == '2'){
      Serial.println("Close!");
      close();
      }
   }
      
    }
    
    
    
  
    
   
   
  
  
