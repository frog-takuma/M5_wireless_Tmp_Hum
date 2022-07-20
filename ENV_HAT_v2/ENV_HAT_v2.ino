#include "BluetoothSerial.h"
//Bluetoothライブラリ
#include <M5StickC.h>
//I2Cを使うためのライブラリインクルード
#include <Wire.h>
//ENV Hatの温度湿度を使うためのライブラリ
#include "DHT12.h"
//ENV Hatの温度湿度を使うためのライブラリを変数化
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

DHT12 dht12;
BluetoothSerial SerialBT;
 
// the setup routine runs once when M5StickC starts up
void setup(){
  // Initialize the M5StickC object
  M5.begin();
  Serial.begin(115200);
  SerialBT.begin("ESP32test");
  
  //ディスプレイ設定
  M5.Lcd.setRotation(3);//横向きにする
  M5.Lcd.setTextFont(2);
  M5.Lcd.fillScreen(BLACK);//背景色黒くする
  // I2C初期化
  Wire.begin(0, 26);  
}
 
// the loop routine runs over and over again forever
void loop() {
 
  // 気温
  float tmp = dht12.readTemperature();
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("Temp: %2.1f C", tmp);

  // 湿度
  float hum = dht12.readHumidity();
  M5.Lcd.setCursor(0, 40);
  M5.Lcd.printf("Humi: %2.0f %%", hum);  

  M5.Lcd.setCursor(0, 60);
  M5.Lcd.printf("%f",hum);  
    
  //SerialBT.println();
  SerialBT.printf("%2.0f_%2.1f",hum,tmp);
  
  // 1秒待機
  delay(1000);
}
