/*
Sound Portal: Internet Connected Infinity Mirror Table

author(s): 
		Jorge Rojas

description:
		Code will control communication with the node server
		to drive a neopixel strip and a speaker. 
*/
#include "application.h"
#include "neopixel/neopixel.h"

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D2
#define PIXEL_COUNT 60
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

//COLORS
#define RED strip.Color(255,0,0)
#define GREEN strip.Color(0,255,0)
#define BLUE strip.Color(0,0,255)
#define YELLOW strip.Color(255,255,0)
#define MAGENTA strip.Color(255,0,255)
#define WHITE strip.Color(255,255,255)

int patternIndex = -1;

void setup() 
{

	Spark.function("setPattern", setPattern);

	strip.begin();
	strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{
	if (patternIndex == 0) {
		sprite(PIXEL_COUNT, RED, WHITE, BLUE, 90);
	}
	if (patternIndex == 1) {
		snake(RED, WHITE, 3);
	}
	if (patternIndex == 2) {
		rainbow(20);
	}
	// sprite(PIXEL_COUNT, strip.Color(255,0,0), strip.Color(0,255,0), strip.Color(255,255,0), 90);
	// twinkleRand(5,strip.Color(255,255,255),strip.Color(255, 0, 100),90);
	// rainbow(20);
}

int setPattern(String command) {
	if (command == "sprite") {
		patternIndex = 0;
		return 1;
	}
	if (command == "snake") {
		patternIndex = 1;
		return 1;
	}
	if (command == "rainbow") {
		patternIndex = 2;
		return 2;
	}
	else {
		return -1;
	}
}

void sprite(int num, uint32_t c0, uint32_t c1, uint32_t c2, int wait) {
		
	uint32_t colors[] = {c0, c1, c2};
	
	for (int i=0; i < num; i++){
		int colorIndex = random(3);
		strip.setPixelColor(random(strip.numPixels()), colors[colorIndex]);
	}
	
	strip.show();
	delay(wait);
}

void snake(uint32_t bg, uint32_t snake, int length){

	for (int i = 0; i < PIXEL_COUNT; i++) {
		stripSet(bg, 0);
		for (int j = 0; j < length; j++) {
			strip.setPixelColor(i + j, snake);
			strip.show();
			delay(30);
		}
	}
}

void rainbow(uint8_t wait) {
	uint16_t i, j;
	
	for(j=0; j<256; j++) {
		for(i=0; i<strip.numPixels(); i++) {
			strip.setPixelColor(i, Wheel((i+j) & 255));
		}
		strip.show();
		delay(wait);
	}
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
	if(WheelPos < 85) {
	 return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	} else if(WheelPos < 170) {
	 WheelPos -= 85;
	 return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	} else {
	 WheelPos -= 170;
	 return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
}

void stripSet(uint32_t c, uint8_t wait) {
	for(uint16_t i=0; i<strip.numPixels(); i++) {
			strip.setPixelColor(i, c);
	}
	// move the show outside the loop
	strip.show();
	delay(wait);
}