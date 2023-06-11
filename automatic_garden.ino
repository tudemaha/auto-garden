#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>

#define soilSensor A0

LiquidCrystal_I2C lcd(0x27, 16, 2);
DS3231 rtc(SDA, SCL);

unsigned int fertilize = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  rtc.begin();

  // rtc.setDOW(SUNDAY);
  // rtc.setTime(20, 44, 0);
  // rtc.setDate(11, 6, 2023);

  lcd.backlight();

  lcd.setCursor(4, 0);
  lcd.print("WELCOME");
  lcd.setCursor(5, 1);
  lcd.print("DUDE!");

  delay(2000);
}

void loop() {
  lcd.clear();
  int sensorValue = analogRead(soilSensor);  
  lcd.setCursor(0, 0);
  lcd.print(rtc.getTimeStr());
  
  String dayNow = rtc.getDOWStr(FORMAT_LONG);
  Time t = rtc.getTime();

  if(dayNow == "Sunday") {
    if(fertilize < 4) {
      lcd.setCursor(11, 0);
      lcd.print("Pupuk");

      fertilize++;
    }
  } else {
    fertilize = 0;
  }

  if(sensorValue > 700) {
    lcd.setCursor(11, 1);
    lcd.print("Siram");
  }
  
  lcd.setCursor(0, 1);
  lcd.print(sensorValue);
  delay(1000);
}
