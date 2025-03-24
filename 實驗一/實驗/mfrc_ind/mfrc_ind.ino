#include<SPI.h> 
#include<MFRC522.h> 
#include <Wire.h>    
#include "rgb_lcd.h" 
#define RST_PIN         9         
#define SS_PIN          10  
 
MFRC522 mfrc522(SS_PIN, RST_PIN); 
rgb_lcd lcd; 
char *reference; 
 
byte uid[]={0xF2, 0x57, 0x15, 0x89};  //這是我們指定的卡片UID，可由讀取UID的程式取得特定卡片的UID，再修改這行 
 
void setup() { 
  Serial.begin(9600); 
  Serial.println("RFID reader is ready!"); 
  lcd.begin(16,2); 
  SPI.begin(); 
  mfrc522.PCD_Init(); 
  mfrc522.PCD_DumpVersionToSerial();} 
 
void loop() { 
  // put your main code here, to run repeatedly: 
   if (mfrc522.PICC_IsNewCardPresent() && 
mfrc522.PICC_ReadCardSerial()) { 
      //byte *id = mfrc522.uid.uidByte;   // 取得卡片的UID 
       
      Serial.print("id:"); 
      lcd.write("id="); 
      for (byte   i = 0; i < 4; i++) {  // 逐一顯示UID碼 
       
        Serial.print(mfrc522.uid.uidByte[i]);       // 以16進位顯示UID值 
        Serial.print(" "); 
        lcd.print(mfrc522.uid.uidByte[i]); 
        lcd.write(" "); 
      } 
      Serial.println(); 
      mfrc522.PICC_HaltA();  // 讓卡片進入停止模式 
      delay(1000); 
    }  
    lcd.clear();
}

