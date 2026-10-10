void setup() {
  Serial.begin(9600);
  // 設定 D3~D6 為按鈕輸入，並啟用內建上拉電阻
  pinMode(3, INPUT_PULLUP); // 按鈕 A
  pinMode(4, INPUT_PULLUP); // 按鈕 B
  pinMode(5, INPUT_PULLUP); // 按鈕 X
  pinMode(6, INPUT_PULLUP); // 按鈕 Y
}

void loop() {
  int btnA = digitalRead(3);
  int btnB = digitalRead(4);
  int btnX = digitalRead(5);
  int btnY = digitalRead(6);

  Serial.print("按鈕A(D3): "); Serial.print(btnA == LOW ? "【按下】" : "放開");
  Serial.print(" | 按鈕B(D4): "); Serial.print(btnB == LOW ? "【按下】" : "放開");
  Serial.print(" | 按鈕X(D5): "); Serial.print(btnX == LOW ? "【按下】" : "放開");
  Serial.print(" | 按鈕Y(D6): "); Serial.println(btnY == LOW ? "【按下】" : "放開");

  delay(200);
}


右手板接線檢查
MPU6050 (#2)：位址確定為 0x69（AD0 已接 5V）。   
4 顆按鈕：
公共端：4 顆按鈕的其中一腳全部串起來，接到 GND。   
訊號端：4 顆按鈕的另一腳，分別拉線接往 Arduino 的 D3, D4, D5, D6 腳位。   