#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include <Servo.h>  
#define PIN      6
#define N_LEDS 39
int sunscreen = 13;
int hat = 12;
int umbrella = 7;
int house = 4;

Servo servo1;
Servo servo2;

int potPosition;
int servoPosition1; 
int servoPosition2; 
int ledBrightness;
int uvLevel[5] = {5, 11, 7, 2, 9};
String cloudiness[5] = {"Mostly Cloudy", "Sunny", "Partly Cloudy", "Cloudy", "Sunny"};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void pulseColor(uint8_t r, uint8_t g, uint8_t b, int delayTime);
void setStripBrightness(uint8_t r, uint8_t g, uint8_t b, int brightness);
void smoothServoMove(Servo &servo, int targetPosition);
void readPot(int day);

void setup() {

  Serial.begin(9600);
  
  strip.begin();
  strip.show();
  servo1.attach(3);
  servo2.attach(9);
  servoPosition1 = 0;
  servoPosition2 = 180;

  pinMode(sunscreen, OUTPUT);
  pinMode(hat, OUTPUT);
  pinMode(umbrella, OUTPUT);
  pinMode(house, OUTPUT);
  
}

//read where the potentiometer is rotated to
void loop() {
  
  potPosition = analogRead(A0);
  Serial.println(potPosition);

  if (potPosition >= 100 && potPosition < 280) {
    readPot(4);
  }
  else if (potPosition >= 300 && potPosition < 480) {
    readPot(3);
  }
  else if (potPosition >= 500 && potPosition < 680) {
    readPot(2);
  }
  else if (potPosition >= 700 && potPosition < 780) {
    readPot(1);
  }
  else if (potPosition >= 800 && potPosition < 980){
    readPot(0);
  }
}

//read selected day off potentiometer
void readPot(int day) { 

  if (cloudiness[day] == "Cloudy") {
    servoPosition1 = 30;
    servoPosition2 = 110;
  }
  else if (cloudiness[day] == "Mostly Cloudy") {
    servoPosition1 = 20;
    servoPosition2 = 60;
  }
  else if (cloudiness[day] == "Partly Cloudy") {
    servoPosition1 = 150;
    servoPosition2 = 140;
  }
  else {
    servoPosition1 = 150;
    servoPosition2 = 20;
  }
  servo1.write(servoPosition1);
  servo2.write(servoPosition2);

  if (uvLevel[day] <= 2) {
    digitalWrite(sunscreen, LOW);
    digitalWrite(hat, LOW);
    digitalWrite(umbrella, LOW);
    digitalWrite(house, LOW);
    setStripBrightness(255, 247, 165, 35);
  }
  else if (uvLevel[day] > 2 && uvLevel[day] <= 5) {
    digitalWrite(sunscreen, HIGH);
    digitalWrite(hat, LOW);
    digitalWrite(umbrella, LOW);
    digitalWrite(house, LOW);
    setStripBrightness(255, 222, 85, 75);
  }
  else if (uvLevel[day] > 5 && uvLevel[day] <= 7) {
    digitalWrite(sunscreen, HIGH);
    digitalWrite(hat, HIGH);
    digitalWrite(umbrella, LOW);
    digitalWrite(house, LOW);
    setStripBrightness(255, 196, 48, 75);
  }
  else if (uvLevel[day] > 7 && uvLevel[day] <= 10) {
    digitalWrite(sunscreen, HIGH);
    digitalWrite(hat, HIGH);
    digitalWrite(umbrella, HIGH);
    digitalWrite(house, LOW);
    pulseColor(255, 85, 0, 85);
  }
  else {
    digitalWrite(sunscreen, HIGH);
    digitalWrite(hat, HIGH);
    digitalWrite(umbrella, HIGH);
    digitalWrite(house, HIGH);
    pulseColor(255, 0, 0, 40);
  }

  Serial.println(cloudiness[day]);
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
}
