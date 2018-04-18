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

// Particle class for controling the LED
LEDStatus blinkLED;

void setup()
{
}

void loop()
{
  // Physical position is flipped on board to provide a more natual left to right feel,
  // so we subtract our final value from 255 to "flip" it.
  // analogRead values are divided by 16 to convert from a 4095 max to 255.
  int redPotVal = 255 - analogRead(RED_POT) / 16;
  int greenPotVal = 255 - analogRead(GREEN_POT) / 16;
  int bluePotVal = 255 - analogRead(BLUE_POT) / 16;

  //useRGBClass(redPotVal, greenPotVal, bluePotVal);
  useLEDStatusClass(redPotVal, greenPotVal, bluePotVal);
}

void useRGBClass(int red, int green, int blue) {
  RGB.control(true);

  int brightnessPotVal = 255 - analogRead(BRIGHTNESS_POT) / 16;

  // Map R, G, B Pots to R, G, B values for the LED
  RGB.color(red, blue, green);

  // Map brightness pot to value
  RGB.brightness(brightnessPotVal);
}

void useLEDStatusClass(int red, int green, int blue) {
  // Set to false in case we're switching between modes
  RGB.control(false);

  LEDSpeed blinkSpeed = LED_SPEED_SLOW;
  LEDSpeed lastBlinkSpeed;

  int blinkRatePotVal = 255 - analogRead(BLINK_RATE_POT) / 16;

  // Convert the R, G, B values to Hex
  long RGBHex = (red << 16) | (green << 8) | blue;

  // Map blink rate pot to values
  // If the blinkRate is less than 85, the light should blink slowly (LED_SPEED_SLOW)
  // If the blinkRate is between 85 and 169, the light should blink slowly (LED_SPEED_NORMAL)
  // If the blinkRate is above 170, the light should blink fast (LED_SPEED_FAST
  // We also need to make sure that the blink rate isn't reset if the pot didn't change enough to trigger one
  if (blinkRatePotVal < 85 && lastBlinkSpeed != LED_SPEED_SLOW) {
    blinkSpeed = LED_SPEED_SLOW;
  } else if (blinkRatePotVal > 85 && blinkRatePotVal < 170 && lastBlinkSpeed != LED_SPEED_NORMAL) {
    blinkSpeed = LED_SPEED_NORMAL;
  } else if (lastBlinkSpeed != LED_SPEED_FAST) {
    blinkSpeed = LED_SPEED_FAST;
  }

  lastBlinkSpeed = blinkSpeed;
  // Set the color, pattern and speed and activate our LED
  blinkLED.setColor(RGBHex);
  blinkLED.setPattern(LED_PATTERN_BLINK);
  blinkLED.setSpeed(blinkSpeed);
  if (!blinkLED.isActive()) blinkLED.setActive(true);
}
