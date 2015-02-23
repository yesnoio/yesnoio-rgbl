# yesnoio-rgbl
Want more control over your Adafruit NeoPixels (WS2812)? Consider using this little library!
This solution does not modify or override any part of the Adafruit NeoPixel library.
Additionally, it adjusts for primary & secondary colors automatically,
providing consistent brightness across the spectrum.

Just include the file & pass colors to the Adafruit NeoPixel library via the rgbl() function:

strip.setPixelColor(0, rgbl(255, 255, 0, 128));
strip.show(); // sets pixel 0 to yellow @ 50%
