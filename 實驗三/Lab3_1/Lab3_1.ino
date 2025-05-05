#include <RH_RF95.h> 
    #include <SoftwareSerial.h> 
    SoftwareSerial SSerial(2, 3); // RX, TX 
    #define COMSerial SSerial 
    #define ShowSerial Serial 
    RH_RF95<SoftwareSerial> rf95(COMSerial); 
    int ledPin = 8;
void setup() { 
    ShowSerial.begin(115200); 
    pinMode(ledPin, OUTPUT);
    ShowSerial.println("RF95 client test."); 
  
    if (!rf95.init()) { 
        ShowSerial.println("init failed"); 
        while (1); 
    } 
    rf95.setFrequency(433.0); 
} 


void loop() { 
  int intensity = 0;
  int a = 100;

    
 
    ShowSerial.println("Sending to rf95_server"); 
    // Send a message to rf95_server 
     
   /*if (ShowSerial.available()) { 
       val = ShowSerial.read(); 
     }  
   ShowSerial.print(val);*/ 
    uint8_t data[] ="E 100";///設定訊息 
    analogWrite(ledPin, a);
    rf95.send(data,sizeof(data)); 
    rf95.waitPacketSent(); 
    // Now wait for a reply 
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN]; 
    uint8_t len = sizeof(buf); 
/* 
    if (rf95.waitAvailableTimeout(3000)) { 
        // Should be a reply message for us now 
        if (rf95.recv(buf, &len)) { 
            ShowSerial.print("got reply: "); 
            ShowSerial.println((char*)buf); 
        } else { 
            ShowSerial.println("recv failed"); 
        } 
    } else { 
        ShowSerial.println("No reply, is rf95_server running?"); 
    } 
*/
  delay(1000);
}