/*

To upload to your Gemma or Trinket:
1) Select the proper board from the Tools->Board Menu
2) Select USBtinyISP from the Tools->Programmer
3) Plug in the Gemma/Trinket, make sure you see the green LED lit
4) For windows, install the USBtiny drivers
5) Press the button on the Gemma/Trinket - verify you see
the red LED pulse. This means it is ready to receive data
6) Click the upload button above within 10 seconds
*/

// TO FIX
// impossible d'uploader sur le trinket quand le fader est branché sur l'input 3
// (le bootloader se met pas en marche)


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define FADERPIN        A1   // GPIO 2 = ANALOG 1 
#define LEDPIN          1
#define NUMPIXELS      16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

int sensorValue = 0;
float temp = 0;
int value = 0;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pinMode(FADERPIN, INPUT);
}



void loop() {

  sensorValue = analogRead(FADERPIN);
  temp = 255*pow(sensorValue/1023.,10);
  value = min(255, temp);
  
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(value,value,value));
    pixels.show();
  }


}
