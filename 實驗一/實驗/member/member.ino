#include<SPI.h> 
#include<MFRC522.h> 
#include <Wire.h>    
#include "rgb_lcd.h" 
//設定PIN腳 
#define RST_PIN         9        
#define SS_PIN          10
// 宣告 RFID 讀取物件 
MFRC522 mfrc522(SS_PIN, RST_PIN); 
// 宣告 LCD 物件 
rgb_lcd lcd; 
 
 int colorR = 0;
         int colorG = 0;
         int colorB = 255;

// 會員結構體 
struct Member { 
  String cardNumber; 
  String name; 
}; 
 
// 設定會員列表 
const int number = 2; // 會員數量 
Member members[number] = { 
{"c9815789", "Member1"},  // 將"XXXXXX" 替換為會員1的實際RFID卡號 
{"67b848e0","sujia"}
}; 
 
void setup() { 
  Serial.begin(9600); 
  Serial.println("RFID reader is ready!"); 
 pinMode(6, OUTPUT);
  //**//lcd初始化 
  lcd.begin(16, 2);
  //**//SPI初始化 
  SPI.begin();
 //**//MFRC522初始化 
  mfrc522.PCD_Init();
  mfrc522.PCD_DumpVersionToSerial(); 
} 


void loop() { 
 //檢測RFID卡 
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) { 
    // 讀取 RFID 卡號 
    String cardNumber = ""; 
    for (byte i = 0; i < mfrc522.uid.size; i++) { 
      cardNumber += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""); 
      cardNumber += String(mfrc522.uid.uidByte[i], HEX); 
    } 
    Serial.println("Card Number: " + cardNumber); 
     
    // 比對 RFID 卡號 
    bool memberFound = false; 
    for (int i = 0; i < number; i++) { 
      if (cardNumber == members[i].cardNumber) { 
        Serial.println("Access Granted - Welcome, " + members[i].name); 
        lcd.clear(); 
        lcd.print("Welcome, "); 
        lcd.print(members[i].name); 

        

        memberFound = true; 
        break; 
      } 
    } 
     
    // 如果不是會員 
    if (!memberFound) { 
      lcd.clear();
      colorB = 0;
      colorG = 0;
      colorR = 255;
        lcd.setRGB(colorR, colorG, colorB);
        lcd.print("fuck you");
 analogWrite(6, 100);
     for(int i = 0; i < 3; i++){
      analogWrite(6, 100);
      delay(100);
      analogWrite(6, 0);
      delay(100);
     }
    }else{
      Serial.println("Hi");
      lcd.clear();
        analogWrite(6, 200);
      colorB = 255;
      colorG = 0;
      colorR = 0;
        lcd.setRGB(colorR, colorG, colorB);
        lcd.print("HihHi");

        for(int i = 0; i < 3; i++){
      analogWrite(6, 100);
      delay(200);
      analogWrite(6, 0);
      delay(200);
     }
    } 
     
    delay(1000); // 延遲一秒避免連續讀取 
      colorB = 0;
      colorG = 0;
      colorR = 0;
        lcd.setRGB(colorR, colorG, colorB);
         analogWrite(6, 0);
    lcd.clear(); 
    lcd.print("Waiting for card"); 
  }}  