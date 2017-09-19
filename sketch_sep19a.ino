#include <Adafruit_NeoPixel.h>

// Low power NeoPixel earrings example.  Makes a nice blinky display
// with just a few LEDs on at any time...uses MUCH less juice than
// rainbow display!
 
#define PIN 0
#define D1 1
#define D2 2
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(20, PIN);
 
uint8_t  mode   = 0, // Current animation effect
         offset = 0; // Position of spinny eyes
uint32_t color2  = 0; // Start red
uint32_t color   = 0; // Start red
uint32_t prevTime;

uint16_t brightness = 0;

void setup() {
  static uint8_t  i;
  pixels.begin();
  pixels.setBrightness(255); // 1/3 brightness
  prevTime = millis();
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);

  for(i=0;i<12;i++){
     pixels.setPixelColor(i, (brightness*(color2>>16)/255),(brightness*(color2>>8&0xff)/255),(brightness*(color2&0xff)/255));
  }
  for(;i<20;i++){
     pixels.setPixelColor(i, (brightness*(color>>16)/255),(brightness*(color>>8&0xff)/255),(brightness*(color&0xff)/255));
  }
  pixels.show();
}
int fader = 60;

char reardisp [12] = {0};
char frontdisp [8] = {0};
void loop() {
  static uint8_t  rear,front;
  static uint8_t brightness2 = 0;
  uint32_t t;
  char orange[4] = {0,11,5,4};
  int i=0;

  //for(i=0;i<12;i++){
  if(brightness2 == brightness){
    if(brightness == 100)
      brightness = 0;
    else{
      brightness = 100;
      color2 = random(0xFFFFFF);
      color = random(0xFFFFFF);
    }

    
  }

  if(brightness2 < brightness)
    brightness2++;
  else if(brightness2 > brightness){
    brightness2--;
    brightness2--;
    brightness2--;
    brightness2--;
  }
 
  pixels.clear();

  for(i=0;i<12;i++){
     pixels.setPixelColor(i, (brightness2*(color>>16)/255),(brightness2*(color>>8&0xff)/255),(brightness2*(color&0xff)/255));
  }
  for(;i<20;i++){
     pixels.setPixelColor(i, (brightness2*(color>>16)/255),(brightness2*(color>>8&0xff)/255),(brightness2*(color&0xff)/255));
  }
  pixels.show();
  delay(10);
  


}
