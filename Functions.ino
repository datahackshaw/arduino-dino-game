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


//Functions.ino


int read_LCD_buttons() {
  adc_key_in  = analogRead(0);

  if (adc_key_in > 1000) return btnNONE;

  if (adc_key_in  < 10)  return btnRIGHT;
  if (adc_key_in < 110)  return btnUP;
  if (adc_key_in  < 300)  return btnDOWN;
  if (adc_key_in < 450)  return btnLEFT;
  if (adc_key_in  < 700)  return btnSELECT;

  return btnNONE;
}

void updateLcd()  {
  for (int i = 0; i <= 15; i++) {
    lcd.setCursor(i, 1);
    lcd.write(runnerArea[i]);
  }
  lcd.setCursor(1, 0);
  lcd.write(jump);
}

void drawBarrier()  {
  runnerArea[0] = 32;
  runnerArea[15] = 32;
}

void printScore()  {
  lcd.setCursor(7, 0);
  lcd.print("Score: ");
  lcd.setCursor(14,  0);
  lcd.print(score);
}

void showSplashScreen(int delayTime, boolean  wait_for_start) {
  lcd.home();
  lcd.setCursor(3,0);
  lcd.print("Dino Game!");
  lcd.setCursor(0, 1);
  lcd.print("UP to Jump!     ");
  drawSplashGraphics();
  delay(delayTime);
  if (wait_for_start) {
    while (read_LCD_buttons()  != btnSELECT) {
      delay(50);
    }
  }
  lcd.clear();
}

void  drawRandChar() {
  lcd.setCursor(random(3, 15), 1);
  lcd.write(byte(random(1,  3)));
}

void drawSplashGraphics() {
  lcd.setCursor(1, 1);
  lcd.write(byte(0));
  drawRandChar();
  drawRandChar();
  drawRandChar();
}

void showCrashScreen()  {
  lcd.setCursor(4, 1);
  lcd.print("Game Over!");
  delay(2500);
  lcd.setCursor(4, 1);
  lcd.print("Best: ");
  lcd.setCursor(10, 1);
  lcd.print("      ");
  lcd.setCursor(10, 1);
  if (EEPROMReadInt(0) <=  score) {
    EEPROMWriteInt(0, score);
  }
  lcd.print(EEPROMReadInt(0));
  while (true) {
    digitalWrite(13, !digitalRead(13));
    delay(500);
  }
}

void EEPROMWriteInt(int address, int value)
{
  byte two =  (value & 0xFF);
  byte one = ((value >> 8) & 0xFF);

  EEPROM.update(address,  two);
  EEPROM.update(address + 1, one);
}

int EEPROMReadInt(int address)
{
  long two = EEPROM.read(address);
  long one = EEPROM.read(address + 1);

  return ((two << 0) & 0xFFFFFF) + ((one << 8) & 0xFFFFFFFF);
}