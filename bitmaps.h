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
// bitmaps.h
byte dino[8] = {
  0b00000,
  0b00111,
  0b00111,
  0b10110,
  0b11111,
  0b01010,
  0b01010,
  0b00000
};

byte cacti[8] = {
  0b00100,
  0b00101,
  0b10101,
  0b10101,
  0b10111,
  0b11100,
  0b00100,
  0b00000
};

byte bird[8] = {
  0b00000,
  0b00000,
  0b10000,
  0b11111,
  0b01110,
  0b01101,
  0b01000,
  0b00000
};

byte block[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
