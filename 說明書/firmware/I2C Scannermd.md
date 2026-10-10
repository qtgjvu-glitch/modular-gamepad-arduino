#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);
  Serial.println("\nI2C 設備掃描測試中...");
}

void loop() {
  byte error, address;
  int nDevices = 0;

  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("找到 I2C 設備！位址：0x");
      if (address<16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println();
      nDevices++;
    }
  }
  if (nDevices == 0)
    Serial.println("未找到任何 I2C 設備，請檢查焊接或接線！\n");
  
  delay(2000);
}




硬體接線：
VCC (紅) $\rightarrow$ Arduino 5V（或 3.3V）   
GND (黑) $\rightarrow$ Arduino GND   
SCL (白) $\rightarrow$ Arduino A5   
SDA (紫) $\rightarrow$ Arduino A4   
AD0 (黃) $\rightarrow$ 先接 Arduino GND   