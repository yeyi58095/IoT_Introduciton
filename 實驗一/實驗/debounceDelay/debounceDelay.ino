# define buttonPin 2
# define ledPin 4

int ledState = HIGH;
int buttonState;
int lastButtonState = LOW;

unsigned long lastDebounceTime = 0;
unsigned long bounceDelay = 50;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
}

void loop() {
  // put your main code here, to run repeatedly:
   int reading = digitalRead(buttonPin);

   if(reading != lastButtonState){
    lastButtonS
   }
}
