/*
Sound Portal: Internet Connected Infinity Mirror Table

author(s): 
		Estefania Ortiz, Jorge Rojas

description:
		Code will control communication with the node server
		to drive a neopixel strip and a speaker. 
*/
#include <stdlib.h>
#include "application.h"
#include "neopixel/neopixel.h"

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define DELAY 
#define PIXEL_PIN D2
#define PIXEL_COUNT 60
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

//COLORS
#define OFF strip.Color(0,0,0)
#define RED strip.Color(255,0,0)
#define BLUE strip.Color(0,0,255)
#define GREEN strip.Color(0,255,0)
#define AQUA strip.Color(0,255,255)
#define YELLOW strip.Color(255,255,0)
#define MAGENTA strip.Color(255,0,255)
#define WHITE strip.Color(255,255,255)

//Default colors until modified by setColor functions
uint32_t c1 = RED; 
uint32_t c2 = GREEN;
uint32_t c3 = BLUE;
int patternIndex = -1;

void setup() 
{

	Spark.function("setColor1", setColor1);
	Spark.function("setColor2", setColor2);
	Spark.function("setColor3", setColor3);
	Spark.function("setPattern", setPattern);


	strip.begin();
	strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{
	if (patternIndex == 0) {
		strobe(c1, 200);
	}
	if (patternIndex == 1) {
		sprite(PIXEL_COUNT, c1, c2, c3, 90);
	}
	if (patternIndex == 2) {
		snake(c1, c2, 3);
	}
	if (patternIndex == 3) {
		rainbow(20);
	}
	if (patternIndex == -1) {
		stripSet(OFF, 0);
	}
}

int setColor1(String command) {
	c1 = strToColor(command);
}

int setColor2(String command) {
	c2 = strToColor(command);
}

int setColor3(String command) {
	c3 = strToColor(command);
}

int setPattern(String command) {

	if (command == "strobe") {
		patternIndex = 0;
		return 1;
	}
	if (command == "sprite") {
		patternIndex = 1;
		return 1;
	}
	if (command == "snake") {
		patternIndex = 2;
		return 1;
	}
	if (command == "rainbow") {
		patternIndex = 3;
		return 1;
	}
	if (command == "off") {
		patternIndex = -1;
		return 1;
	}
	else {
		return -1;
	}
}

void strobe(uint32_t c, int wait) {
	for (int i = 0; i < PIXEL_COUNT; i++) {
		strip.setPixelColor(i, c);
	}
	strip.show();
	delay(wait);
	stripSet(OFF,0);
	delay(wait);  	
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

uint32_t strToColor(String strColor) {
	String temp;
	char * cpoint;
	uint32_t r, g, b;
	char red[4], green[4], blue[4];

	temp = "0x" + strColor.substring(0,2);
	temp.toCharArray(red, 4);
	temp = "0x" + strColor.substring(2,4);
	temp.toCharArray(green, 4);
	temp = "0x" + strColor.substring(4,6);
	temp.toCharArray(blue, 4);

	r = strtol(red, &cpoint, 16);
	g = strtol(green, &cpoint, 16);
	b = strtol(blue, &cpoint, 16);

	return strip.Color(r, g, b);
}
