void setup() {
  Serial.begin(9600);
  // 設定 D2 為按鈕輸入，並開啟內建上拉電阻
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  int xValue = analogRead(A0);  // 讀取 X 軸 (0 ~ 1023)
  int yValue = analogRead(A1);  // 讀取 Y 軸 (0 ~ 1023)
  int swState = digitalRead(2); // 讀取按鈕 (1 為放開，0 為按下)

  Serial.print("X軸: ");
  Serial.print(xValue);
  Serial.print(" | Y軸: ");
  Serial.print(yValue);
  Serial.print(" | 按鈕: ");
  if (swState == LOW) {
    Serial.println("【按下！】");
  } else {
    Serial.println("放開");
  }

  delay(200); // 每 0.2 秒更新一次
}





//PS2 搖桿 5 針腳對應表
//搖桿模組標籤     作用說明                    接到 Arduino UNO 的位置
//GND            負極（接地）                接洞洞板 GND 總線（或 Arduino GND）
//+5V (或 VCC)   正極（電源）                 接洞洞板 5V 總線（或 Arduino 5V）
//VRX            X軸左右搖動（類比訊號）       接 Arduino 的 A0 腳位   
//VRY            Y 軸上下搖動（類比訊號）      接 Arduino 的 A1 腳位   
//SW             搖桿向下按壓開關（數位訊號）   接 Arduino 的 D2 腳位   