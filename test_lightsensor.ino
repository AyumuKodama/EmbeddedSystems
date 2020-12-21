int buzzer = 12;                                        // the pin where you will put the LED
int lightSense = A7;                  // the analog pin where you put your sensorLED
int ledPin = 10;
int light = 0;
int count = 0;
int base = 1024;
int test = 1024;
int test2 = 1024;
int test3 = 1024;
int dark = 125;


int wait = 3;                  // the speed of the readings; a lower number is a higher speed
int samples = 100;                   // the amount of samples to compare to make one reading

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
}


void loop() {                                            
for(count = 0; count < samples; count++) {// remember the lowest value out of many readings
   light = analogRead(lightSense);
   delay(wait);                                   // the sensor needs a delay here to catch its breath
   if (light < test){
    test3 = light;                                            // remember the 3 lowest readings
    test2 = test3;
    test = test2;
   }
  }
  if (test < dark && test2 < dark && test3 < dark){//this value was taken from trial-and-error
    tone(buzzer, 2300);
    digitalWrite(ledPin, HIGH);
  } else {
    noTone(buzzer);
    digitalWrite(ledPin, LOW);
    base = test;                                         // if the lowest test reading is higher than the base, base will be reset
  }
  test = 1024;
}
