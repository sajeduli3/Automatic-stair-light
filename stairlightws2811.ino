
#include <FastLED.h>


#define NUM_LEDS 60

#define DATA_PIN 3
#define CLOCK_PIN 13

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance;

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

// This function sets up the ledsand tells the controller about them
void setup() {

   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin, INPUT); // Sets the echoPin as an Input
   Serial.begin(9600);
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
  // 	delay(2000);

    FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness (255);
  
}


void loop() {
    digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
if (distance <= 10){



  
   // Move a single white led 
   for(int i=0;  i< NUM_LEDS; i++ ) {
      // Turn our current led on to white, then show the leds
      leds[i] = CRGB::White;

      // Show the leds (only one of which is set to white, from above)
      FastLED.show();

      // Wait a little bit
      delay(30);

     
   }
delay(5000);
for(int i=0;  i< NUM_LEDS; i++ ) {
      // Turn our current led on to white, then show the leds
      leds[i] = CRGB::Black;

      // Show the leds (only one of which is set to white, from above)
      FastLED.show();

      // Wait a little bit
      delay(30); }

   
}}
