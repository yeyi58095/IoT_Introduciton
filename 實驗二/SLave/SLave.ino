#include <SoftwareSerial.h> 
#include <Wire.h> 
#include "rgb_lcd.h" 
SoftwareSerial BTSerial(10, 9); // RX, TX 
rgb_lcd lcd; 
int ledPin = 4;
int soundPin = 2;
void setup() { 
Serial.begin(9600); 
BTSerial.begin(9600); 
lcd.begin(16, 2); 
lcd.setRGB(255, 255, 255); // 白色背景（正常接收時） 
lcd.print("Starting ..."); 
delay(1000); 
lcd.clear(); 
} 
void loop() { 
// 從序列監控視窗讀取輸入字元 
if (Serial.available()) { 
  analogWrite(soundPin, 0);
char c = Serial.read(); 
if (c == '1' || c == '0' || c == '2' || c == '3') { 
BTSerial.write(c); // 傳送到 Master 
lcd.clear(); 
lcd.setRGB(0, 255, 0); // 綠色背景：從端發送中 
} 
} 
// 接收來自 Master 的訊息 
if (BTSerial.available()) { 
char c = BTSerial.read(); 
digitalWrite(ledPin, c == '1' ? HIGH : LOW); 


if(c == '1'){
  analogWrite(soundPin, 100);
}else if(c == '2'){
  analogWrite(soundPin, 200);
}else if(c == '3'){
  analogWrite(soundPin, 254);
}else{
  analogWrite(soundPin, 0);
}
Serial.println(c); 
lcd.clear();


lcd.clear(); 


Serial.print ("Salve-receive："); 
Serial.println(c); 
lcd.print("Salve-receive：");
lcd.println(c);
} 
} 