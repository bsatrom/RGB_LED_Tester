/*
 * Project RGB_LED_Tester
 * Description:  Example project for controlling the onboard Particle RGB LED with potentiometers
 * Author: Brandon Satrom <brandon@particle.io>
 * Date: 04/17/2018
 */

// Potentiometer pins
#define RED_POT A0
#define GREEN_POT A1
#define BLUE_POT A2
#define BRIGHTNESS_POT A3
#define BLINK_RATE_POT A4

// Variables for analog readings on pots
int redPotVal;
int greenPotVal;
int bluePotVal;
int brightnessPotVal;
int blinkRatePotVal;

void setup()
{
  RGB.control(true);
}

void loop()
{
  // Physical position is flipped on board to provide a more natual left to right feel,
  // so we subtract our final value from 255 to "flip" it.
  // analogRead values are divided by 16 to convert from a 4095 max to 255.
  redPotVal = 255 - analogRead(RED_POT) / 16;
  greenPotVal = 255 - analogRead(GREEN_POT) / 16;
  bluePotVal = 255 - analogRead(BLUE_POT) / 16;
  brightnessPotVal = 255 - analogRead(BRIGHTNESS_POT) / 16;
  blinkRatePotVal = 255 - analogRead(BLINK_RATE_POT) / 16;

  // Map R, G, B Pots to R, G, B values for the LED
  RGB.color(redPotVal, greenPotVal, bluePotVal);

  // Map brightness pot to value
  RGB.brightness(brightnessPotVal);

  // Map blink rate pot to values
  // If the blinkRate is less than 85, the light should breathe (LED_PATTERN_FADE)
  // If the blinkRate is between 85 and 169, the light should blink slowly (LED_SPEED_NORMAL)
  // If the blinkRate is above 170, the light should blink fast (LED_SPEED_FAST
  if (blinkRatePotVal < 85) {
    LEDStatus blinkLED(LED_PATTERN_FADE, LED_SPEED_NORMAL);
    blinkLED.setActive(true);
  } else if (blinkRatePotVal > 85 && blinkRatePotVal < 170) {
    LEDStatus blinkLED(LED_PATTERN_BLINK, LED_SPEED_NORMAL, LED_PRIORITY_NORMAL);
    blinkLED.setActive(true);
  } else {
    LEDStatus blinkLED(LED_PATTERN_BLINK, LED_SPEED_FAST, LED_PRIORITY_NORMAL);
    blinkLED.setActive(true);
  }
}
