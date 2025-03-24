int x = 100;
boolean state;
void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  state = false;
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(6, x);
  delay(50);

  
  if(!state){
    if(x > 0){
      x --;
    }else{
      x = 0;
      
    }
    
  }


}
