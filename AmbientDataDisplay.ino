
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket

#endif

#include <Servo.h>  

#define PIN      6
#define N_LEDS 39

Servo servo1;
Servo servo2;


int potPosition;
int servoPosition1; 
int servoPosition2; 
int ledBrightness;
int uvLevel[5] = {6, 11, 4, 2, 9};
String cloudiness[5] = {"Mostly Cloudy", "Sunny", "Partly Cloudy", "Cloudy", "Sunny"};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void pulseColor(uint8_t r, uint8_t g, uint8_t b, int delayTime);
void setStripBrightness(uint8_t r, uint8_t g, uint8_t b, int brightness);
void smoothServoMove(Servo &servo, int targetPosition);
void readPot(int day);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show();
  servo1.attach(9);
  servo2.attach(10);
  servoPosition1 = 0;
  servoPosition2 = 180;


}

void loop() {
  // put your main code here, to run repeatedly:
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

void readPot(int day) {

  if (cloudiness[day] == "Cloudy") {
        servoPosition1 = 180;
        servoPosition2 = 0;
        setStripBrightness(255, 247, 165, 35);

      }
      else if (cloudiness[day] == "Mostly Cloudy") {
        servoPosition1 = 135;
        servoPosition2 = 45;
        setStripBrightness(255, 222, 85, 75);
      }
      else if (cloudiness[day] == "Partly Cloudy") {
        servoPosition1 = 90;
        servoPosition2 = 135;
        setStripBrightness(255, 213, 0, 100);
      }
      else {
        servoPosition1 = 0;
        servoPosition2 = 180;
        pulseColor(255, 0, 0, 10);
      }
   servo1.write(servoPosition1);
  servo2.write(servoPosition2);   
  } 

void pulseColor(uint8_t r, uint8_t g, uint8_t b, int delayTime) {
  // Fade in (brightness from 0 to 255)
  for (int brightness = 0; brightness <= 100; brightness += 5) {
    setStripBrightness(r, g, b, brightness);
    delay(delayTime);
  }
  
  // Fade out (brightness from 255 to 0)
  for (int brightness = 100; brightness >= 0; brightness -= 5) {
    setStripBrightness(r, g, b, brightness);
    delay(delayTime);
  }
}
void setStripBrightness(uint8_t r, uint8_t g, uint8_t b, int brightness) {
  uint32_t color = strip.Color((r * brightness) / 255, 
                               (g * brightness) / 255, 
                               (b * brightness) / 255);
  for (int i = 0; i < N_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
