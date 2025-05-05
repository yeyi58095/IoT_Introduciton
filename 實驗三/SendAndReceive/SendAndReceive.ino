#include <RH_RF95.h>
#include <SoftwareSerial.h>

int X;  // 辨識字節
const int lightSensorPin = A0;
int ledPin = 8;
SoftwareSerial SSerial(2, 3);  // RX, TX
#define COMSerial SSerial
#define ShowSerial Serial
RH_RF95<SoftwareSerial> rf95(COMSerial);

void setup() {
  pinMode(ledPin, OUTPUT);
  ShowSerial.begin(115200);
  pinMode(lightSensorPin, INPUT);
  if (!rf95.init()) {
    ShowSerial.println("init failed");
    while (1)
      ;
  }
  rf95.setFrequency(433.0);
}

void loop() {
  // 讀取亮度感測器並轉換為 PWM 值
  //int sensorValue = analogRead(lightSensorPin);
  /// int sensorValue = 500;
  // int pwmValue = map(sensorValue, 0, 1023, 255, 0); // 低亮度時 PWM 值更高

  // 封裝數據：地址 'B' (ASCII 66) + PWM 值
  // uint8_t data[2] = {69, (uint8_t)pwmValue};
  // Serial.println(data[0]);
  // 發送數據至主端
  //rf95.send(data, sizeof(data));
  //  rf95.waitPacketSent();

  // 等待主端回傳的 PWM 值
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  if (rf95.waitAvailableTimeout(3000)) {
    if (rf95.recv(buf, &len)) {
      if (buf[0] == 69) {
        ShowSerial.print("主端回傳 PWM: ");
        ShowSerial.println(buf[1]);
        int pwm = buf[1];
        Serial.println(pwm);
        int value = 255 - pwm;
        analogWrite(ledPin, value);
        uint8_t dat[2] = { 69, (uint8_t)value };
        rf95.send(dat, sizeof(dat));
        rf95.waitPacketSent();
      }
    }
  }
  delay(100);
}