#include <Adafruit_NeoPixel.h>

#define PIN 0
#define D1 1
#define D2 2
#define MAX_COLORS 12

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(20, PIN);

                
uint32_t color_old = 0;
uint32_t color = 0;
uint32_t colors[MAX_COLORS] = {0};

uint32_t prevTime, faderTime;

uint16_t brightness = 0;

uint8_t Red(uint32_t color)
{
  return (color >> 16) & 0xFF;
}
uint8_t Green(uint32_t color)
{
  return (color >> 8) & 0xFF;
}
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

  colors[0] = pixels.Color(0xFF, 0x0D, 0xFF); // FF0DFF
  colors[1] = pixels.Color(0x0D, 0xFF, 0x24); //0DFF24
  colors[2] = pixels.Color(0xFF, 0x00, 0x00);
  colors[3] = pixels.Color(0x0C, 0x0C, 0xE8); // 0C0CE8
  colors[4] = pixels.Color(0xDA, 0xFF, 0x34); // DAFF34
  colors[5] = pixels.Color(0xC8, 0x34, 0xFF); // C834FF

  for (i = 0; i < MAX_COLORS; i++)
  {
    if (colors[i] == 0)
      colors[i] = pixels.Color(random(255), random(255), random(255));
  }
}
int fader = 60;

uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;

#define CHANGE_INTERVAL 400
void loop()
{
  static uint8_t rear, front, rotate = 0;
  static uint8_t brightness2 = 100, TotalSteps = 255, Index = 0;
  uint32_t t, change_interval = CHANGE_INTERVAL;
  char orange[4] = {0, 11, 5, 4};
  static int i = 0;

  red = ((Red(color_old) * (TotalSteps - Index)) + (Red(color) * Index)) / TotalSteps;
  green = ((Green(color_old) * (TotalSteps - Index)) + (Green(color) * Index)) / TotalSteps;
  blue = ((Blue(color_old) * (TotalSteps - Index)) + (Blue(color) * Index)) / TotalSteps;

  if (i < 20)
  {
    pixels.setPixelColor(i, red, green, blue);
    i++;
  }
  else
  {
    if (prevTime < millis() - 2)
    {
      pixels.show();
      prevTime = millis();
      Index++;
      i = 0;
      if (Index > 254)
      {
        Index = 0;
        color_old = colors[rotate];

        if (rotate + 1 > MAX_COLORS - 1)
          color = colors[0];
        else
          color = colors[rotate + 1]; 
          rotate++;
        if (rotate > MAX_COLORS - 1)
          rotate = 0;
      }
    }
    else
    {
      ;
    }
  }
}
