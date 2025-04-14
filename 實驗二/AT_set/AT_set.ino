#include <SoftwareSerial.h>   // 引用函式庫

// 定義連接藍牙模組的序列埠
SoftwareSerial BT(10, 9); // bt_Tx接收腳, bt_Rx傳送腳
char val;  // 接收資料的變數

void setup() {
  Serial.begin(9600);   // 與電腦序列埠連線速率
  Serial.println("BT is ready!");
  
  // 設定藍牙模組的連線速率
  // HC-05，用38400
  BT.begin(38400);
}

void loop() {
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }

  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (BT.available()) {
    val = BT.read();
    Serial.print(val);
  }
}

//0021:11:01CCFC
