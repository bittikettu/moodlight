#include <Adafruit_NeoPixel.h>

// Low power NeoPixel earrings example.  Makes a nice blinky display
// with just a few LEDs on at any time...uses MUCH less juice than
// rainbow display!

#define PIN 0
#define D1 1
#define D2 2
#define MAX_COLORS 12

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(20, PIN);

uint8_t mode = 0,    // Current animation effect
    offset = 0;      // Position of spinny eyes
uint32_t color2 = pixels.Color(255,255,255); // Start red

uint32_t color_old = 0;
uint32_t color = pixels.Color(3,22,100);  // Start red

uint32_t colors[MAX_COLORS] = {0};



uint32_t prevTime,faderTime;

uint16_t brightness = 0;


uint8_t Red(uint32_t color)
{
    return (color >> 16) & 0xFF;
}

// Returns the Green component of a 32-bit color
uint8_t Green(uint32_t color)
{
    return (color >> 8) & 0xFF;
}

// Returns the Blue component of a 32-bit color
uint8_t Blue(uint32_t color)
{
    return color & 0xFF;
}




void setup()
{
  static uint8_t i;
  pixels.begin();
  pixels.setBrightness(255); // 1/3 brightness
  prevTime = millis();
  faderTime = millis();
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);

  colors[0] = pixels.Color(0xFF,0x0D,0xFF); // FF0DFF
  colors[1] = pixels.Color(0x0D,0xFF,0x24); //0DFF24
  colors[2] = pixels.Color(0xFF,0x00,0x00); 
  colors[3] = pixels.Color(0x0C,0x0C,0xE8); // 0C0CE8
  colors[4] = pixels.Color(0xDA,0xFF,0x34); // DAFF34
  colors[5] = pixels.Color(0xC8,0x34,0xFF); // C834FF

  for(i = 0; i< MAX_COLORS;i++){
    if(colors[i] == 0)
      colors[i] = pixels.Color(random(255),random(255),random(255));
  }
  //color_old = colors[0];
  //color = colors[1];//random(0xFFFFFF);

  /*for (i = 0; i < 12; i++)
  {
    pixels.setPixelColor(i, (brightness * (color2 >> 16) / 255), (brightness * (color2 >> 8 & 0xff) / 255), (brightness * (color2 & 0xff) / 255));
  }
  for (; i < 20; i++)
  {
    pixels.setPixelColor(i, (brightness * (color >> 16) / 255), (brightness * (color >> 8 & 0xff) / 255), (brightness * (color & 0xff) / 255));
  }
  pixels.show();*/
}
int fader = 60;

uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;

#define CHANGE_INTERVAL 400
void loop()
{
  static uint8_t rear, front,rotate=0;
  static uint8_t brightness2 = 100,TotalSteps = 255, Index=0;
  uint32_t t, change_interval = CHANGE_INTERVAL;
  char orange[4] = {0, 11, 5, 4};
  static int i = 0;

  //for(i=0;i<12;i++){
  /*if (brightness2 == brightness)
  {
    if (brightness == 100)
      brightness = 0;
    else
    {
      brightness = 100;
      //color2 = random(0xFFFFFF);
      //color = random(0xFFFFFF);
    }
  }*/
  

  red = ((Red(color_old) * (TotalSteps - Index)) + (Red(color) * Index)) / TotalSteps;
  green = ((Green(color_old) * (TotalSteps - Index)) + (Green(color) * Index)) / TotalSteps;
  blue = ((Blue(color_old) * (TotalSteps - Index)) + (Blue(color) * Index)) / TotalSteps;


  if(i < 20){
    //pixels.setPixelColor(i, (brightness2 * (color >> 16) / 255), (brightness2 * (color >> 8 & 0xff) / 255), (brightness2 * (color & 0xff) / 255));
    pixels.setPixelColor(i, red, green, blue);
    i++;
  }
  else {    
    if(prevTime < millis()-2){
      pixels.show();
      prevTime = millis();
      Index++;
      i=0;
      if(Index > 254) {
        Index = 0;
        color_old = colors[rotate];
        
        if(rotate+1 > MAX_COLORS-1)
          color = colors[0];
        else
          color = colors[rotate+1];//random(0xFFFFFF);
        rotate++;
        if(rotate > MAX_COLORS-1)
          rotate = 0;
      }
        
      //pixels.clear();
      //pixels.setBrightness(random(0xFF)/*255/400*(millis()-prevTime)*/);

    }
    else {
      
    }
  }

    //}
  
  /*for (; i < 20; i++)
  {
    pixels.setPixelColor(i, (brightness2 * (color2 >> 16) / 255), (brightness2 * (color2 >> 8 & 0xff) / 255), (brightness2 * (color2 & 0xff) / 255));
  }*/
  
  //delay(10);
}
