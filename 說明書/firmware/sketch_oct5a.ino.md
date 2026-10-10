#include <Wire.h>

// MPU-6050 I2C 位址
const int MPU_LEFT  = 0x68; // 左手板
const int MPU_RIGHT = 0x69; // 右手板

// 儲存姿態角度 (簡易計算)
int16_t AcX1, AcY1, AcZ1;
int16_t AcX2, AcY2, AcZ2;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // 初始化左手 MPU6050
  Wire.beginTransmission(MPU_LEFT);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // 喚醒 MPU6050
  Wire.endTransmission(true);

  // 初始化右手 MPU6050
  Wire.beginTransmission(MPU_RIGHT);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // 初始化按鈕腳位
  pinMode(2, INPUT_PULLUP); // 搖桿 SW 按鈕
  pinMode(3, INPUT_PULLUP); // 按鈕 A
  pinMode(4, INPUT_PULLUP); // 按鈕 B
  pinMode(5, INPUT_PULLUP); // 按鈕 X
  pinMode(6, INPUT_PULLUP); // 按鈕 Y
}

void loop() {
  // 1. 讀取左手 MPU6050 (0x68)
  Wire.beginTransmission(MPU_LEFT);
  Wire.write(0x3B); // 從 ACCEL_XOUT_H 開始讀取
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_LEFT, 6, true);
  AcX1 = Wire.read() << 8 | Wire.read();
  AcY1 = Wire.read() << 8 | Wire.read();
  AcZ1 = Wire.read() << 8 | Wire.read();

  // 2. 讀取右手 MPU6050 (0x69)
  Wire.beginTransmission(MPU_RIGHT);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_RIGHT, 6, true);
  AcX2 = Wire.read() << 8 | Wire.read();
  AcY2 = Wire.read() << 8 | Wire.read();
  AcZ2 = Wire.read() << 8 | Wire.read();

  // 3. 讀取搖桿與按鈕
  int joyX = analogRead(A0);
  int joyY = analogRead(A1);
  int joySW = (digitalRead(2) == LOW) ? 1 : 0;
  int btnA  = (digitalRead(3) == LOW) ? 1 : 0;
  int btnB  = (digitalRead(4) == LOW) ? 1 : 0;
  int btnX  = (digitalRead(5) == LOW) ? 1 : 0;
  int btnY  = (digitalRead(6) == LOW) ? 1 : 0;

  // 4. 輸出統一通訊封包格式到 Serial Monitor
  // 格式：L_X,L_Y,L_Z | R_X,R_Y,R_Z | JoyX,JoyY,JoySW | A,B,X,Y
  Serial.print("L:");
  Serial.print(AcX1); Serial.print(","); Serial.print(AcY1); Serial.print(","); Serial.print(AcZ1);
  Serial.print(" | R:");
  Serial.print(AcX2); Serial.print(","); Serial.print(AcY2); Serial.print(","); Serial.print(AcZ2);
  Serial.print(" | JOY:");
  Serial.print(joyX); Serial.print(","); Serial.print(joyY); Serial.print(","); Serial.print(joySW);
  Serial.print(" | BTN:");
  Serial.print(btnA); Serial.print(btnB); Serial.print(btnX); Serial.println(btnY);

  delay(50); // 20Hz 刷新率
}