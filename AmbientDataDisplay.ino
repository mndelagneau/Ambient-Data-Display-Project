#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include <Servo.h>  

#define LED_PIN    6
#define LED_COUNT 60

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int potPosition;
int servoPosition1; 
int servoPosition2; 
int ledBrightness;
int uvLevel[4];
String cloudiness[4];
int cloudinessValue[4];


void setup() {
  
  myservo.attach(9);
  servoPosition1 = 0;
  servoPosition2 = 180;

  cloudiness = ["Mostly Cloudy", "Sunny", "Partly Cloudy", "Cloudy", "Sunny"];

}

void loop() {
  
  potPosition = analogRead(A0);

  if (potPosition < 205) {
    readPot(0);
  }
  else if (potPosition >= 205 && potPosition < 410) {
    readPot(1);
  }
  else if (potPosition >= 410 && potPosition < 615) {
    readPot(2);
  }
  else if (potPosition >= 615 && potPosition < 820) {
    readPot(3);
  }
  else {
    readPot(4);
  }

}

void readPot(day) {

  if (cloudiness[day] = "Cloudy") {
        servoPosition1 = 180;
        servoPosition2 = 0;
      }
      else if (cloudiness[day] = "Mostly Cloudy") {
        servoPosition1 = 135;
        servoPosition2 = 45;
      }
      else if (cloudiness[day] = "Partly Cloudy") {
        servoPosition1 = 90;
        servoPosition2 = 135;
      }
      else {
        servoPosition1 = 0;
        servoPosition2 = 180;
      }
  } 

}



