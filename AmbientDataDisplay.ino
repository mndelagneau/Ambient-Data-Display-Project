#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include <Servo.h>  
#define PIN      6
#define N_LEDS 39
#define BUILT_IN_LED_PIN_SUNSCEEN 13
#define BUILT_IN_LED_PIN_HAT 12
#define BUILT_IN_LED_PIN_UMBRELLA 11
#define BUILT_IN_LED_PIN_HOUSE 10

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
  
  strip.begin();
  strip.show();
  servo1.attach(9);
  servo2.attach(10);
  servoPosition1 = 0;
  servoPosition2 = 180;

  pinMode(BUILT_IN_LED_PIN_SUNSCEEN, OUTPUT);
  pinMode(BUILT_IN_LED_PIN_HAT, OUTPUT);
  pinMode(BUILT_IN_LED_PIN_UMBRELLA, OUTPUT);
  pinMode(BUILT_IN_LED_PIN_HOUSE, OUTPUT);
  
}

//read where the potentiometer is rotated to
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

//read selected day off potentiometer
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

  if (uvLevel[day] <= 2) {
    digitalWrite(BUILT_IN_LED_PIN_SUNSCREEN, LOW);
    digitalWrite(BUILT_IN_LED_PIN_HAT, LOW);
    digitalWrite(BUILT_IN_LED_PIN_UMBRELLA, LOW);
    digitalWrite(BUILT_IN_LED_PIN_HOUSE, LOW);
  }
  else if (uvLevel[day] > 2 && uvLevel[day] <= 5) {
    digitalWrite(BUILT_IN_LED_PIN_SUNSCREEN, HIGH);
    digitalWrite(BUILT_IN_LED_PIN_HAT, LOW);
    digitalWrite(BUILT_IN_LED_PIN_UMBRELLA, LOW);
    digitalWrite(BUILT_IN_LED_PIN_HOUSE, LOW);
  }
  else if (uvLevel[day] > 5 && uvLevel[day] <= 7) {
    digitalWrite(BUILT_IN_LED_PIN_SUNSCREEN, HIGH);
    digitalWrite(BUILT_IN_LED_PIN_HAT, HIGH);
    digitalWrite(BUILT_IN_LED_PIN_UMBRELLA, LOW);
    digitalWrite(BUILT_IN_LED_PIN_HOUSE, LOW);
  }
  else if (uvLevel[day] > 7 && uvLevel[day] <= 10) {
    digitalWrite(BUILT_IN_LED_PIN_SUNSCREEN, HIGH);
    digitalWrite(BUILT_IN_LED_PIN_HAT, HIGH);
    digitalWrite(BUILT_IN_LED_PIN_UMBRELLA, HIGH);
    digitalWrite(BUILT_IN_LED_PIN_HOUSE, LOW);
  }
  else {
    digitalWrite(BUILT_IN_LED_PIN_SUNSCREEN, HIGH);
    digitalWrite(BUILT_IN_LED_PIN_HAT, HIGH);
    digitalWrite(BUILT_IN_LED_PIN_UMBRELLA, HIGH);
    digitalWrite(BUILT_IN_LED_PIN_HOUSE, HIGH);
  }
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
