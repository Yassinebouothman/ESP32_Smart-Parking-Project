
//I used arduino cloud IoT platform for this project


#include "arduino_secrets.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
// #include <WiFi.h>
#include <ESP32Servo.h>
#include "thingProperties.h"

LiquidCrystal_I2C lcd(0x27,16,2);
Servo barrier;
// #define ssid ""
// #define password ""

const int ledg = 14;
const int ledr = 12;
const int sensor1 = 5;
const int sensor2 = 16;

const int brightness = 34;

int flag1 = 0;
int flag2 = 0;

void setup() {
  Serial.begin(9600);
  delay(1500);

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(ledr, OUTPUT);
  pinMode(ledg, OUTPUT);

  lcd.init();
  lcd.backlight();
  analogWrite(brightness, 100);


  barrier.attach(4);
  barrier.write(180);
  spots_available =4;
  // WiFi.begin(ssid, password);                                      //try to connect with wifi
  // Serial.print("Connecting to ");
  // Serial.print(ssid);

  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
    // Serial.println("");
    // Serial.println("WiFi connected");
    // Serial.println("IP address: ");
    // Serial.println(WiFi.localIP());  
    lcd.setCursor(3,0);
    lcd.print("Welcome to");
    lcd.setCursor(1,1);
    lcd.print("Smart Parking");
    delay(2000);
    lcd.clear();
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection,false);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  

}

void loop() {
  ArduinoCloud.update();

      lcd.setCursor(4,0);
      lcd.print("Welcome!");
      lcd.setCursor(2,1);
      lcd.print("Spots left=");
      lcd.setCursor(14,1)  ;    
      lcd.print(spots_available);
      
  if(digitalRead(sensor1) == LOW && flag1==0){
    if(spots_available > 0){
      flag1 = 1;
      if (flag2 == 0){
        barrier.write(90);
        digitalWrite(ledg, HIGH);
        digitalWrite(ledr, LOW);        
        spots_available = spots_available - 1;

      }
    }
    else{
      digitalWrite(ledr, HIGH);
      digitalWrite(ledg, LOW);
     

    }
}

  if(digitalRead(sensor2) == LOW && flag2 == 0){
    flag2 = 1;
    if(flag1 == 0){
      barrier.write(90);
      digitalWrite(ledg, HIGH);
      digitalWrite(ledr, LOW);
      spots_available = spots_available + 1;

    }
  }

  if(flag1 == 1 && flag2 == 1){
    delay (250);
    barrier.write(180);
    digitalWrite(ledr, LOW);
    digitalWrite(ledg, LOW);
    flag1 = 0, flag2 = 0;
  }

  }

