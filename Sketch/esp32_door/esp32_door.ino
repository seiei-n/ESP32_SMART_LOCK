#include <ESP32Servo.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

const int SERVO = 12; // サーボモーターピン
char input;

Servo servo; // サーボクラス
RTC_DATA_ATTR int bootCount = 0;
void open()
{
  servo.attach(SERVO);
  servo.write(180);
  delay(500);
  servo.detach();
}
void close()
{
  servo.attach(SERVO);
  servo.write(90);
  delay(500);
  servo.detach();
}
void deep_sleep()
{
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_15,1);
  esp_deep_sleep_start();
}

void setup()
{
  pinMode(GPIO_NUM_15, INPUT_PULLUP);
  SerialBT.begin("ESP32");
  Serial.begin(115200);
  Serial.print("OK!!");
  delay(5000);
  if (SerialBT.available() > 0)
  {  
    input = SerialBT.read();
    if (input == '1')
    {
      SerialBT.print("Open!");
      Serial.print("Open!");
      delay(500);
      open();
    }
    else if (input == '2')
    {
      SerialBT.print("Close!");
      Serial.print("Close!")
      delay(500);
      close();
    }
  }
  SerialBT.print("Going to sleep now");
  Serial.print("Going to sleep now");
  deep_sleep();
  
 
}

void loop()
{
  // esp_sleep_enable_ext0_wakeup(GPIO_NUM_15,1);
  // delay(10000);
  // if (SerialBT.available() > 0)
  // {  
  //   input = SerialBT.read();
  //   if (input == '1')
  //   {
  //     SerialBT.print("Open!");
  //     delay(500);
  //     open();
  //   }
  //   else if (input == '2')
  //   {
  //     SerialBT.print("Close!");
  //     delay(500);
  //     close();
  //   }
  // }
  // SerialBT.print("Going to sleep now");
  // Serial.print("Going to sleep now");
  // esp_deep_sleep_start();

  
 
}
