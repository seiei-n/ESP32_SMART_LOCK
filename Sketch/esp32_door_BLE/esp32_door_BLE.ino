#include <ESP32Servo.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLE2902.h>


#define DEVICE_NAME    "ESP32_SMART_LOCK"
#define SPI_SPEED      115200

#define SIGNAL_ERROR    'E'         // (異常発生:Error)
#define SIGNAL_ACK      'A'         // (了解：Acknoledge)
#define SIGNAL_OPEN     'O'         
#define SIGNAL_CLOSE    'C'        


#define SERVICE_UUID           "33f9bdbe-bb12-4aa1-afb7-f18dfa160f2c"
#define CHARACTERISTIC_UUID_TX "8e903bd6-c965-43b4-bbaa-7f3c7dd5f3fe"
#define CHARACTERISTIC_UUID_RX "6a0d9053-4291-4f19-ba6f-03175f331233" 





BLECharacteristic *pCharacteristicTX;
BLECharacteristic *pCharacteristicRX;

bool deviceConnected = false;

const int SERVO = 12; // サーボモーターピン
char input;

Servo servo; // サーボクラス

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




class funcServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
    }
    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
    }
};

class  funcReceiveCallback: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristicRX){
      std::string rxValue = pCharacteristicRX->getValue();
      if (rxValue.length()> 1){
        for (int i = 0; i < rxValue.length(); i++) {
                Serial.print(rxValue[i]);
        }
      }
      else{
        switch (rxValue[0]){
          case SIGNAL_ACK:
              Serial.println("Receive data: [Ack!]");
              break;
          case SIGNAL_OPEN:
              Serial.println("Receive data: [Open!]");
              delay(500);
              open();
              break;
          case SIGNAL_CLOSE:
              Serial.println("Receive data: [Close!]");
              delay(500);
              close();
              break;
          default:
              break;


        }
      }

    }


};




void deep_sleep()
{
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_15,1);
  esp_deep_sleep_start();
}

void doInitialize(){
  Serial.begin(SPI_SPEED);
  pinMode(GPIO_NUM_15, INPUT_PULLUP);

}

void doPrepare(BLEService *pService) {
    // Notify用のキャラクタリスティックを作成する
    pCharacteristicTX = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_TX,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );
    pCharacteristicTX->addDescriptor(new BLE2902());

    // 受信用キャラクタリスティックを作成してシグナル受信時のコールバックを設定する
    pCharacteristicRX = pService->createCharacteristic(
                                           CHARACTERISTIC_UUID_RX,
                                           BLECharacteristic::PROPERTY_WRITE
                                         );
    pCharacteristicRX->setCallbacks(new funcReceiveCallback());
}

void setup()
{
  doInitialize();
  BLEDevice::init(DEVICE_NAME);

  // Serverオブジェクトを作成してコールバックを設定する
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new funcServerCallbacks());
 
    // Serviceオブジェクトを作成して準備処理を実行する
    BLEService *pService = pServer->createService(SERVICE_UUID);
    doPrepare(pService);
 
    // サービスを開始して、SERVICE_UUIDでアドバタイジングを開始する
    pService->start();
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->start();
    Serial.println("Waiting to connect ...");
 
}

void loop()
{
  if(!deviceConnected){
    
  }
  
}


