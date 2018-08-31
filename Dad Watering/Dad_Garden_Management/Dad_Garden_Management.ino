//Version 7-25 with lights controller
// libraries definition
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
#include <SPI.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// pins definition

int pumpPin = 2;
int pumpPin2 = 3;
int pumpPin3 = 4;
int pumpPin4 = 5;
int pumpPin5 = 6;
int pumpPin6 = 7;
int pumpPin7 = 8;
int pumpPin8 = 9;
int lightPin = 10;
int button1 = 0;
int button2 = 1;
int button3 = 2;
int button4 = 3;



//switch
int d =2;
// variables
int levelSensorValue;       // stores the level sensor values
int moistureSensorValue;    // stores the moisture sensor values
int j = 0;


RTC_DS1307 RTC;
LiquidCrystal_I2C lcd(0x27,20,4);

void setup(){
  // serial initialization
  Serial.begin(9600);
  // LCD initialization
  lcd.init();          
  lcd.backlight();     // with Backlight
  lcd.clear();         // clearscreen
  // Wire initialization
  Wire.begin();
  // RTC initialization
  RTC.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__)); 
  
  //Test Date Time
  Serial.print("Kai Watering System Setting up \n");
  Serial.print("Date Today is:\n ");
  DateTime now = RTC.now();
  Serial.print(now.year(), DEC);
  Serial.print("/");
  Serial.print("0");
  Serial.print(now.month(), DEC);
  Serial.print("/");
  Serial.print("0");
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(":");
  Serial.print(now.minute(), DEC);
  Serial.print(":");
  Serial.print(now.second(), DEC);
  Serial.println();
  // Arduino pins initalization
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(button3,INPUT);
  pinMode(button4,INPUT);

  pinMode(pumpPin,OUTPUT);
  pinMode(pumpPin2,OUTPUT);
  pinMode(pumpPin3,OUTPUT);
  pinMode(pumpPin4,OUTPUT);
  pinMode(pumpPin5,OUTPUT);
  pinMode(pumpPin6,OUTPUT);
  pinMode(pumpPin7,OUTPUT);
  pinMode(pumpPin8,OUTPUT);

  
  pinMode(lightPin,OUTPUT);




  
  // LCD initial messages
  lcd.clear();
  lcd.setCursor(0,0);

  lcd.setCursor(0,1);

  lcd.setCursor(0,3);

  // initialization delay
  digitalWrite(pumpPin,HIGH);
  digitalWrite(pumpPin2,HIGH);
  delay(1000); 

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("INITIALIZING");
  display.display();
  delay(1000); 
  display.clearDisplay();

  
  if (! RTC.isrunning()){
    Serial.println("RTC is NOT running!");
    display.clearDisplay();
    display.print("CLOCK MALFUNCTION");
    display.display();
    delay(1000); 
    display.clearDisplay();
    display.display();
  }else{
    Serial.println("RTC is running!");
    display.clearDisplay();
    display.print("CLOCK OK");
    display.display();
    delay(1000); 
    display.clearDisplay();
    display.display();
  }
}






void loop(){
  // RTC parameters definition
  DateTime myRTC = RTC.now();
  int H = myRTC.hour();
  int M = myRTC.minute();
  int S = myRTC.second();
  RightHour();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("KIT's Garden Control");
  //display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.print("Next Watering:");

  
  if (H<9||H>15){
    display.print("9:00AM");
  }
  else{
    display.print("3:00PM");
  }
  
  //display.print(myRTC.year(), DEC);
  //display.print("/");
  //display.print("0");
  //display.print(myRTC.month(), DEC);
  //display.print("/");
  //display.print(myRTC.day(), DEC);
  //display.print("     ");
  display.println();

  display.setTextSize(2);
  display.setTextColor(WHITE);
    display.print(myRTC.hour(), DEC);
  display.print(":");
  if (myRTC.minute() <10){
    display.print("0");
  }
  display.print(myRTC.minute(), DEC);
  display.print(":");
  if (myRTC.second() <10){
    display.print("0");
  }
  display.print(myRTC.second(), DEC);
  display.display();




  
  if((H == 9) && (M == 00) && (S == 00)){
    Serial.println();
    Serial.print("*****************Starting pump*******************");
    Serial.println();
    display.clearDisplay();
    display.display();
    display.setCursor(0,0);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.println("MORNING");
    display.println("WATERING");
    display.display();
    digitalWrite(pumpPin,LOW);
    delay(3000);
    digitalWrite(pumpPin,HIGH);
    digitalWrite(pumpPin2,LOW);
    delay(6000);
    digitalWrite(pumpPin2,HIGH);
    Serial.println();
    Serial.print("*****************Stopping pump*******************");
    Serial.println();
    display.clearDisplay();
    display.display();
  }

  if((H == 15) && (M == 00) && (S == 00)){
    Serial.println();
    Serial.print("*****************Starting pump*******************");
    Serial.println();
    display.clearDisplay();
    display.display();
    display.setCursor(0,0);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.println("AFTERNOON");
    display.println("WATERING");
    display.display();
    digitalWrite(pumpPin,LOW);
    delay(4000);
    digitalWrite(pumpPin,HIGH);
    digitalWrite(pumpPin2,LOW);
    delay(7000);
    digitalWrite(pumpPin2,HIGH);
    Serial.println();
    Serial.print("*****************Stopping pump*******************");
    Serial.println();
    display.clearDisplay();
    display.display();
  }

  d=digitalRead(button1);
  if(d==0 ){
    Serial.println();
    Serial.print("*****************Manual Override Starting pump*******************");
    Serial.println();
    display.clearDisplay();
    display.display();
    display.setCursor(0,0);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.println("Button");
    display.println("2");
    display.display();
    digitalWrite(pumpPin,LOW);
    delay(1000);
    digitalWrite(pumpPin,HIGH);
    digitalWrite(pumpPin2,LOW);
    delay(1000);
    digitalWrite(pumpPin2,HIGH);
 
    display.clearDisplay();
    display.display();
  }














  

  digitalWrite(pumpPin,HIGH);
  digitalWrite(pumpPin2,HIGH);
  digitalWrite(pumpPin3,HIGH);
  digitalWrite(pumpPin4,HIGH);
  digitalWrite(pumpPin5,HIGH);
  digitalWrite(pumpPin6,HIGH);
  digitalWrite(pumpPin7,HIGH);
  digitalWrite(pumpPin8,HIGH);

  delay(100);
  display.clearDisplay();
  
}



// Real Time Clock Function
void RightHour()
{
  DateTime Now = RTC.now();
  String clock_date = "  Date: ";
  String clock_hour = "   Time: ";
  
  int _day = Now.day();
  int _month = Now.month();
  int _year = Now.year();
  
  clock_date += fixZero(_day);
  clock_date += "/";
  clock_date += fixZero(_month);
  clock_date += "/";
  clock_date += _year;
  
  int _hour = Now.hour();
  int _minute = Now.minute();
  int _second = Now.second();
  
  clock_hour += fixZero(_hour);
  clock_hour += ":";
  clock_hour += fixZero(_minute);
  clock_hour += ":";
  clock_hour += fixZero(_second);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(clock_date);
  lcd.setCursor(0, 1);
  lcd.print(clock_hour);
  

}


String fixZero(int i)
{
  String ret;
  if (i < 10) ret += "0";
  ret += i;
  return ret;
}



