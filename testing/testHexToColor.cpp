#include <string>
#include <iostream>

using namespace std;

uint32_t strToColor(string strColor) {
	string temp;
	char * cpoint;
	uint32_t r, g, b;
	char red[4], green[4], blue[4];

	temp = "0x" + strColor.substr(0,2);
	strncpy(red, temp.c_str(), 4);
	temp = "0x" + strColor.substr(2,4);
	strncpy(green, temp.c_str(), 4);
	temp = "0x" + strColor.substr(4,6);
	strncpy(blue, temp.c_str(), 4);

	r = strtol(red, &cpoint, 16);
	g = strtol(green, &cpoint, 16);
	b = strtol(blue, &cpoint, 16);
	return r;
}

int main()
{
	string color;
	uint32_t colorbyte;
	color = "055";
	colorbyte = atoi(color.c_str());
	cout << "The red integer value is " << colorbyte;
}
