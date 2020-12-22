int buzzer = 12;                                      
int lightSense = A7;              
int ledPin = 10;
int light = 0;
int count = 0;
int test = 1024;
int test2 = 1024;
int test3 = 1024;
int dark = 125;


int wait = 3;              
int samples = 100;                   

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
}


void loop() {                                            
for(count = 0; count < samples; count++) {
   light = analogRead(lightSense);
   delay(wait);       
   if (light < test){
    test3 = light;                          
    test2 = test3;
    test = test2;
   }
  }
  if (test < dark && test2 < dark && test3 < dark){
    tone(buzzer, 2300);
    digitalWrite(ledPin, HIGH);
  } else {
    noTone(buzzer);
    digitalWrite(ledPin, LOW);                                
  }
  test = 1024;
}
