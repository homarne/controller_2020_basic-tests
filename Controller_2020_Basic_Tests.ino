/*  OctoWS2811 BasicTest.ino - Basic RGB LED Test
    http://www.pjrc.com/teensy/td_libs_OctoWS2811.html
    Copyright (c) 2013 Paul Stoffregen, PJRC.COM, LLC

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

  Required Connections
  --------------------
    pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
    pin 14: LED strip #2    All 8 are the same length.
    pin 7:  LED strip #3
    pin 8:  LED strip #4    A 100 ohm resistor should used
    pin 6:  LED strip #5    between each Teensy pin and the
    pin 20: LED strip #6    wire to the LED strip, to minimize
    pin 21: LED strip #7    high frequency ringining & noise.
    pin 5:  LED strip #8
    pin 15 & 16 - Connect together, but do not use
    pin 4 - Do not use
    pin 3 - Do not use as PWM.  Normal use is ok.

  This test is useful for checking if your LED strips work, and which
  color config (WS2811_RGB, WS2811_GRB, etc) they require.
*/

#include <OctoWS2811.h>

const int ledsPerStrip = 144;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

int sw1;
int sw2;
int sw3;
int sw4;

int knob1;
int knob2;

void setup() {

Serial.begin(9600);
  
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);

  
  leds.begin();
  leds.show();
}

//#define RED    0xFF0000
//#define GREEN  0x00FF00
//#define BLUE   0x0000FF
//#define YELLOW 0xFFFF00
//#define PINK   0xFF1088
//#define ORANGE 0xE05800
//#define WHITE  0xFFFFFF

// full power except white at half power
//#define RED    0xFF0000
//#define GREEN  0x00FF00
//#define BLUE   0x0000FF
//#define YELLOW 0xFFFF00
//#define PINK   0xFF1088
//#define ORANGE 0xE05800
//#define WHITE  0x7F7F7F

// quarter power
#define RED    0x400000
#define GREEN  0x004000
#define BLUE   0x000040
#define YELLOW 0x404000
#define PINK   0x400422
#define ORANGE 0x381600
#define WHITE  0x3F3F3F

// 1/11h power (???)...

//#define RED    0x160000
//#define GREEN  0x001600
//#define BLUE   0x000016
//#define YELLOW 0x101400
//#define PINK   0x120009
//#define ORANGE 0x100400
//#define WHITE  0x101010

#define LED_OFF  0x000000

void loop() {

// all sw off - auto loop
// knob1 + knob2 sets speed
// else if sw2 on: knob2 pics color
// else if sw3 on: always green
// else if sw4 on: always red

  //int microsec = 2000000 / leds.numPixels();  // change them all in 2 seconds
  int microsec =   2000000 / leds.numPixels();  // change them all in 2 seconds

  // uncomment for voltage controlled speed
  // millisec = analogRead(A9) / 40;

  colorWipe(RED, microsec);
  colorWipe(GREEN, microsec);
  colorWipe(BLUE, microsec);
  colorWipe(YELLOW, microsec);
  colorWipe(PINK, microsec);
  colorWipe(ORANGE, microsec);
  colorWipe(WHITE, microsec);
}

void colorWipe(int color, int wait){
  
  for (int i=0; i < leds.numPixels(); i++) {
    switchWipe();
    leds.setPixel(i, color);
    leds.show();
    int knob_1 = analogRead(A8);
    int knob_2 = analogRead(A9);
    delayMicroseconds((knob_1 + knob_2)*100);
  }
}

void switchWipe(){
  
//    int final_color = color;
//    if (digitalRead(16) == HIGH) final_color = RED;
//    if (digitalRead(17) == HIGH) final_color = GREEN;
//    if (digitalRead(18) == HIGH) final_color = BLUE;
//    if (digitalRead(19) == LOW) final_color = WHITE;
  for (int i=0; i < leds.numPixels(); i++) {
    if (i % 144 == 0){
      //Serial.println(i);
      int final_color;
      (digitalRead(16) == HIGH) ? final_color = WHITE : final_color = LED_OFF;
      for (int j=i; j < i+3; j++) {
         leds.setPixel(j, final_color);
      }
      (digitalRead(17) == HIGH) ? final_color = WHITE : final_color = LED_OFF;
      for (int j=i+3; j < i+3+3; j++) {
         leds.setPixel(j, final_color);
      }
      (digitalRead(18) == HIGH) ? final_color = WHITE : final_color = LED_OFF;
      for (int j=i+6; j < i+3+6; j++) {
         leds.setPixel(j, final_color);
      }
      (digitalRead(19) == HIGH) ? final_color = WHITE : final_color = LED_OFF;
      for (int j=i+9; j < i+3+9; j++) {
         leds.setPixel(j, final_color);
      }
    }
  }
}
