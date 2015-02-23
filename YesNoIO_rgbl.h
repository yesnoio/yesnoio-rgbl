/**
 * @yesnoio
 * 
 * A library to allow the brightness of each Adafruit NeoPixel (WS2812)
 * to be controlled with relative ease. Instead of passing
 * a raw HEX value (0xFFFF00) into the Adafruit library,
 * pass the result of the rgbl() function.
 *   The function automatically adjusts levels so
 *   secondary colors (which require up to 3 LEDs in the 'pixel')
 *   are the same perceived brightness as red, green or blue
 *   (which only require one LED in the 'pixel').
 * @example
 *   strip.setPixelColor(4, rgbl(255, 255, 0, 128));
 *   strip.show(); // sets neopixel 4 to yellow @ 50%
 */

/**
 * Restrict an integer to a value between 0 and 255
 * @param  val The value to restrict
 * @return     The restricted value
 */
int valueConfine(int val) {
  if (val < 0) val = 0;
  if (val > 255) val = 255;
  return val;
}

/**
 * Adjust value by intensity.
 * @param  v  The initial value from 0 to 255.
 * @param  i  The desired intensity from 0 to 255.
 * @return
 */
int intensity(int v, int i) {
  return valueConfine(v) * valueConfine(i) / 255;
}

/**
 * Convert an RGB value to a long int.
 * This long int can likely be passed into a function
 *   expecting a hex color value (e.g. 0xffffff).
 * @param  r The red value.
 * @param  g The green value.
 * @param  b The blue value
 * @return   A long int color value.
 */
long rgbToLong(int r, int g, int b) {
   return ((long)r << 16L) | ((long)g << 8L) | (long)b;
}

/**
 * Get a long int representing R, G & B combined at a specified luminance.
 * @example
 *   long color = rgbl(255, 255, 255, 128); // (white at 50% brightness)
 * @param  r The red value from 0 - 255.
 * @param  g The green value from 0 - 255.
 * @param  b The blue value from 0 - 255.
 * @param  l The desired luminance from 0 - 255.
 * @return   A long int color value.
 */
long rgbl(byte r, byte g, byte b, byte l) {
  r = intensity(r,l);
  g = intensity(g,l);
  b = intensity(b,l);

  // Since we're likely dealing with tri-color led housings,
  // a single color may require more than one led to attain
  // the desired effect. We perform a simple adjustment here
  // to reduce undesirable fluctuations in brightness.
  int litLeds = 0;
  long totalLum = 0;
  if (r > 0) {
    totalLum += r;
    litLeds++;
  }
  if (g > 0) {
    totalLum += g;
    litLeds++;
  }
  if (b > 0) {
    totalLum += b;
    litLeds++;
  }

  // @todo test this
  //byte minusLum = (int) ( (int) (totalLum / litLeds) / 3);

  // Adjust the total intensity
  byte minusLum = (totalLum / litLeds) / 3;
  r = valueConfine(r - minusLum);
  g = valueConfine(g - minusLum);
  b = valueConfine(b - minusLum);

  return rgbToLong(r,g,b);
}
