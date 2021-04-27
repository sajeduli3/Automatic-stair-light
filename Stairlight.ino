#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define trigPin1 8
#define echoPin1 9
#define trigPin2 10
#define echoPin2 11
#define PIN 3
#define NUMPIXELS 313


long duration, distance, RightSensor,BackSensor,FrontSensor,LeftSensor;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS , PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 20
void setup()
{
Serial.begin (9600);

strip.begin();
strip.setBrightness(50);
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);

}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<312*1; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 312 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
}

void loop() {
strip.clear();  
SonarSensor(trigPin1, echoPin1);
RightSensor = distance;
SonarSensor(trigPin2, echoPin2);
LeftSensor = distance;


Serial.print(LeftSensor);
Serial.print(" - ");
Serial.println(RightSensor);

if (LeftSensor <= 45){
for(int i=0; i<=NUMPIXELS; i++ ) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    strip.setPixelColor(i, strip.Color(255, 0, 125));

    strip.show();   // Send the updated pixel colors to the hardware.

    delay (DELAYVAL); // Pause before next pass through loop
  }
  delay (10);
  rainbowCycle(1);
  for(int i=0; i<=NUMPIXELS; i++)
  {
    strip.setPixelColor(i, strip.Color(0,0,0));
    strip.show();
    delay (DELAYVAL);
  }}

  else if (RightSensor <= 45){
    
    for(int i=NUMPIXELS; i; i-- ) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    strip.setPixelColor(i, strip.Color(0, 255, 255));

   strip.show();   // Send the updated pixel colors to the hardware.

    delay (DELAYVAL); // Pause before next pass through loop
  }
  rainbowCycle(1);
  for(int i=NUMPIXELS; i; i--)
  {
    strip.setPixelColor(i, strip.Color(0,0,0));
    strip.show();
    delay (DELAYVAL);}}
}
  
