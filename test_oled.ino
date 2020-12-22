#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Time.h>
#include <TimeAlarms.h>
Adafruit_BME280 bme; 

int reset = 17;
Adafruit_SSD1306 display(reset);
int height = 32;
int width = 128;
int count = 0;

void setup() {
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  setTime(8,14,0,12,22,20);
  Alarm.alarmRepeat(8,15,0,alarm);
  Alarm.timerRepeat(15,repeat);
  display.clearDisplay();
}

void repeat(){            //code for when alarm repeats every 15 seconds
  display.clearDisplay();
  display.setTextSize(3);
  display.print("WAKE UP");
  delay(1000);
  display.clearDisplay();
}

void alarm(){
  display.clearDisplay();
  display.setTextSize(3);
  display.print("WAKE UP");                         
}

void loop() {
  // put your main code here, to run repeatedly: 
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,5);
  display.print("Temp: ");
  display.print(bme.readTemperature());
  display.println("C");
  display.print("Pressure: ");
  display.print(bme.readPressure()/1000);
  display.println(" kPa");
  display.print("Humidity: ");
  display.print(bme.readHumidity());
  display.println("%");
  display.display();
  delay(1000); 
  display.clearDisplay();
  display.print(hour());
  display.print(":");
  display.print(minute());
  display.display();
}
