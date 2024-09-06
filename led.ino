#include <Adafruit_NeoPixel.h>

#define PIN        3    // Pin connected to NeoPixels
#define NUMPIXELS  528  // Number of pixels in the ring
#define DELAYVAL   0    // Minimal delay for fast changes

// Create an instance of the NeoPixel strip
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Function to convert HSV to RGB color
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

void setup() {
  pixels.begin();  // Initialize NeoPixel strip
}

void loop() {
  static int startHue = 0;  // Variable to track the start of the gradient

  // Loop through each pixel and set its color based on the hue offset
  for(int i = 0; i < NUMPIXELS; i++) {
    int hue = (startHue + (i * 256 / NUMPIXELS)) & 255; // Calculate the hue for each pixel
    pixels.setPixelColor(i, Wheel(hue));  // Assign the color from the Wheel function
  }

  pixels.show();  // Update the strip with new colors

  startHue += 20;  // Larger hue step for faster color changes
  if (startHue >= 256) {
    startHue = 0;  // Wrap around when we reach the end of the color wheel
  }

  delay(DELAYVAL);  // Remove delay for rapid color changes
}
