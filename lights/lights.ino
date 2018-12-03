#include "FastLED.h"
#define NUM_LEDS 179 
CRGB leds[NUM_LEDS];
#define PIN 7

void setup()
{
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
}

// *** REPLACE FROM HERE ***
void loop() {
  //colorWipe(0x00,0x00,0x00, 50);
  colorWipe(0x00,0xff,0x00, 50);
  colorWipe(0x00,0x00,0x00, 50);
  colorWipe(0xff,0x00,0x00, 50);
  colorWipe(0x00,0x00,0x00, 50);
  colorWipe(0x00,0x00,0xff, 50);
  colorWipe(0x00,0x00,0x00, 50);
  colorWipe(0xff,0xff,0x00, 50);
  colorWipe(0x00,0x00,0x00, 50);
  colorWipe(0xff,0x00,0xff, 50);
  colorWipe(0x00,0x00,0x00, 50);
  colorWipe(0x00,0xff,0xff, 50);
  colorWipe(0x00,0x00,0x00, 50);
  RunningLights(0xff,0,0, 50);        // red
  RunningLights(0,0xff,0, 50);
  RunningLights(0,0,0xff, 50);        // blue
  RunningLights(0xff,0,0xff, 50);
  RunningLights(0,0xff,0xff, 50);
  RunningLights(0xff,0xff,0, 50);
  for(int r = 1; r <=5; r++){
  rainbowCycle(2);
  }
  for(int r = 1; r <=5; r++){
  theaterChaseRainbow(50);
  }
  CylonBounce(0xff, 0, 0, 4, 30, 50);
  CylonBounce(0, 0xff, 0, 4, 30, 50);
  CylonBounce(0, 0, 0xff, 4, 30, 50);
}

// ** sylon **
void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  
  delay(ReturnDelay);
}
// ** sylon **

// ** rainbow **
void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_LEDS; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}
// ** rainbow **

// ** colorwipe **
void colorWipe(byte red, byte green, byte blue, int SpeedDelay) {
  for(uint16_t i=0; i<NUM_LEDS; i++) {
      setPixel(i, red, green, blue);
      showStrip();
      delay(SpeedDelay);
  }
}
// ** colorwipe **

// ** theaterRainbow **
void theaterChaseRainbow(int SpeedDelay) {
  byte *c;
  
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < NUM_LEDS; i=i+3) {
          c = Wheel( (i+j) % 255);
          setPixel(i+q, *c, *(c+1), *(c+2));    //turn every third pixel on
        }
        showStrip();
       
        delay(SpeedDelay);
       
        for (int i=0; i < NUM_LEDS; i=i+3) {
          setPixel(i+q, 0,0,0);        //turn every third pixel off
        }
    }
  }
}

byte * tWheel(byte tWheelPos) {
  static byte c[3];
  
  if(tWheelPos < 85) {
   c[0]=tWheelPos * 3;
   c[1]=255 - tWheelPos * 3;
   c[2]=0;
  } else if(tWheelPos < 170) {
   tWheelPos -= 85;
   c[0]=255 - tWheelPos * 3;
   c[1]=0;
   c[2]=tWheelPos * 3;
  } else {
   tWheelPos -= 170;
   c[0]=0;
   c[1]=tWheelPos * 3;
   c[2]=255 - tWheelPos * 3;
  }

  return c;
}
// ** theaterRainbow **

// ** runningLigths **
void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position=0;
  
  for(int i=0; i<NUM_LEDS*2; i++)
  {
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<NUM_LEDS; i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
      }
      
      showStrip();
      delay(WaveDelay);
  }
}
// ** runningLights **

// ---> here we define the effect function <---
// *** REPLACE TO HERE ***

void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}
