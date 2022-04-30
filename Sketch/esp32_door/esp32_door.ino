

#include <ESP32Servo.h>
#include <BluetoothSerial.h>
#include <WiFi.h>
#include <HTTPClinet.h>
const char SSID[] = "server";
const char PASSWORD[] = "solehamugoiyo";
const char URL[] = "http://127.0.0.1:8000/data";


BluetoothSerial SerialBT;

const int SERVO = 12; // サーボモーターピン
char input;

Servo servo; // サーボクラス

void open()
{
  servo.write(90);
  delay(500);
}
void close()
{
  servo.write(180);
  delay(500);
}
void setup()
{
  pinMode(14, OUTPUT);
  servo.attach(SERVO); // サーボモーターの制御ピン設定
  SerialBT.begin(ESP32);
  Serial.begin(115200);
  SerialBT.println("OK!!");
  while (!Serial);
  WiFi.begin(SSID, PASSWORD);
  Serial.print("WiFi connecting");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
  }

  Serial.println(" connected");
}

void loop()
{
  HTTPClient http;
  http.begin(URL);
  int httpCode = http.GET();

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
