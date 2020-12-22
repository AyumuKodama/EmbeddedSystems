#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Time.h>
#include <TimeAlarms.h>               //libraries list
Adafruit_BME280 bme;                  //sets up BME sensor
int reset = 17;                       //RES# pin number for OLED
Adafruit_SSD1306 display(reset);      //sets up display
int buzzer = 12;                      //buzzer number
int lightSense = A7;                  //light sensing LED pin number
int ledPin = 10;                      //alarm LED number
int light = 0;
int count = 0;
int test = 1024;
int test2 = 1024;
int test3 = 1024;
int dark = 125;                       //any value below this is considered dark
int wait = 3;
int samples = 100;

void setup() {
  pinMode(buzzer, OUTPUT); //turns alarm buzzer on
  pinMode(ledPin, OUTPUT); //turns alarm LED on
  bme.begin(0x76);         //turns BME sensor on
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);   //turns display on
  display.display();
  delay(2000);
  display.clearDisplay();
  setTime(8,14,0,12,22,20);         //sets clock time at 8:14AM, 12/22/2020
  Alarm.alarmRepeat(8,15,0,alarm);  //sets up alarm at 8:15AM
  Alarm.timerRepeat(15,repeat);     //sets up alarm so it repeats every 15 seconds
}

void repeat(){            //code for when alarm repeats every 15 seconds
  display.clearDisplay();
  display.setTextSize(3);
  display.print("WAKE UP");
  delay(1000);
  display.clearDisplay();
}

void alarm(){                //what happens when alarm time is reached
  display.clearDisplay();
  display.setTextSize(3);
  display.print("WAKE UP");                 //display changes
  for(count = 0; count < samples; count++) {
   light = analogRead(lightSense);              //light sensing LED turned on
   delay(wait);
   if (light < test){
    test3 = light;                             // remember the 3 lowest light valuess
    test2 = test3;
    test = test2;
   }
  }
  if (test < dark && test2 < dark && test3 < dark){//this 'dark' value was taken from trial-and-error
    tone(buzzer, 2300);                       //buzzer turns on
    digitalWrite(ledPin, HIGH);               //LED turns on
  } else {
    noTone(buzzer);                           //buzzer turns off
    digitalWrite(ledPin, LOW);                //LED turns off
  }
  test = 1024;                              //resets test
}

void loop() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);          //sets up text size and color
  display.setCursor(20,5);              //sets up initial position of text
  display.print("Temp: ");
  display.print(bme.readTemperature());
  display.println("C");                 //prints temperature taken from BME
  display.print("Pressure: ");
  display.print(bme.readPressure()/1000);   //prints pressure taken from BME, converts from Pa to kPa
  display.println(" kPa");
  display.print("Humidity: ");
  display.print(bme.readHumidity());      //prints humidity taken from BME
  display.println("%");
  display.display();
  delay(1000); 
  display.clearDisplay();                   //after a second, BME data is erased to display time
  display.print(hour());
  display.print(":");
  display.print(minute());                //displays time in XX:XX form
  display.display();
}
