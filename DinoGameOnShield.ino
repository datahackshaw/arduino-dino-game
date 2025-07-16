/*
 * Arduino Dino Game for LCD Keypad Shield
 * 
 * A recreation of the Chrome Dino game for Arduino Uno with LCD Keypad Shield
 * 
 * Author: Terminal Technology Tips
 * YouTube: @TerminalTechnologyTips 
 * Date: July 2025
 * 
 * MIT License
 * 
 * Copyright (c) 2025 Terminal Technology Tips
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


// DinoGameOnShield.ino

#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "bitmaps.h"

LiquidCrystal  lcd(8, 9, 4, 5, 6, 7);

int adc_key_in  = 0;

#define btnRIGHT  0
#define  btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define  btnNONE   5

byte runnerArea[16] {32, 32, 32, 32, 32, 32, 32, 32, 32, 32,  32, 32, 32, 32, 32, 32};
byte jump = 32;

int score = 0;
bool freeze_score  = 0;
int obstacleSpacing = 0; // spacing counter

unsigned long previousMillis = 0;
unsigned  long previousMillisLED = 0;
unsigned long jumpTime = 0;
const int jumpLength  = 500;

#define checkSafe runnerArea[1] == 32 || runnerArea[1] == 0

const  byte chance_of_ob = 12; // lower # more obstacles
int speedOfScroller = 300;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);

  lcd.createChar(0, dino);
  lcd.createChar(1, cacti);
  lcd.createChar(2, bird);
  lcd.createChar(3,  block);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(13, OUTPUT);
  randomSeed(A1);
  lcd.clear();
  showSplashScreen(1000, true);
}

void  loop() {
  unsigned long currentMillis = millis();
  unsigned long currentMillisOb  = millis();
  if (currentMillisOb - previousMillis >= speedOfScroller) {
    previousMillis = currentMillisOb;
    
    if (obstacleSpacing > 0) {
      obstacleSpacing--; // count down spacing
      runnerArea[15] = 32; // no obstacle during spacing
    } else {
      // generate obstacle when spacing allows
      if (random(chance_of_ob) == 0) {
        runnerArea[15] = 1;
        obstacleSpacing = 2 + random(3); // 2-4 spaces after obstacle
      } else if (random(chance_of_ob) == 1) {
        runnerArea[15] = 2;
        obstacleSpacing = 2 + random(3); // 2-4 spaces after obstacle
      } else {
        runnerArea[15] = 32;
      }
    }
    
    for (int i =  0; i <= 15; i++) {
      runnerArea[i] = runnerArea[i + 1];
    }
    if  (freeze_score == 0) {
      score++;
    }
  }
  drawBarrier();

  if (read_LCD_buttons() == btnUP) {
    // runnerArea[1] = 32;
    if  (runnerArea[1] != 32 && (runnerArea[1] != 1 || runnerArea[1] != 2)) {
      runnerArea[1]  = 32;
    }
    jump = 0;
    freeze_score = 1;
    jumpTime = millis();
  }
  if (millis() - jumpTime >= jumpLength) {
    if (checkSafe) {
      runnerArea[1]  = 0;
      jump = 32;
      freeze_score = 0;
    } else {
      showCrashScreen();
    }
  }
  updateLcd();
  printScore();

  if (millis() - previousMillisLED  >= 500) {
    previousMillisLED = currentMillis;
    digitalWrite(13, !digitalRead(13));
  }
}