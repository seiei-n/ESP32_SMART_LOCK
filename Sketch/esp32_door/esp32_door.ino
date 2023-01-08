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
void setup()
{
  pinMode(14, OUTPUT);
   // サーボモーターの制御ピン設定
  SerialBT.begin(ESP32);
  Serial.begin(115200);
  SerialBT.println("OK!!");
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_15,1);
 
}

void loop()
{


  if (Serial.available() > 0)
  {
    input = Serial.read();
    if (input == '1')
    {
      Serial.println("Open!");
      digitalWrite(14, HIGH);
      delay(500);

      open();
    }
    else if (input == '2')
    {
      Serial.println("Close!");

      digitalWrite(14, LOW);
      delay(500);
      close();
    }
  }
}
