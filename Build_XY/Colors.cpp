#include "Colors.h"

static map<string, Color> colors;

void initColors()
{
	colors["Aqua"] = Color(000, 255, 255);
	colors["Black"] = Color(000, 000, 000);
	colors["Blue"] = Color(000, 000, 255);
	colors["Fuchsia"] = Color(255, 000, 255);
	colors["Gray"] = Color(128, 128, 128);
	colors["Green"] = Color(000, 128, 000);
	colors["Lime"] = Color(000, 255, 000);
	colors["Maroon"] = Color(128, 000, 000);
	colors["Navy"] = Color(000, 000, 128);
	colors["Olive"] = Color(128, 128, 000);
	colors["Purple"] = Color(128, 000, 128);
	colors["Red"] = Color(255, 000, 000);
	colors["Silver"] = Color(192, 192, 192);
	colors["Teal"] = Color(000, 128, 128);
	colors["White"] = Color(255, 255, 255);
	colors["Yellow"] = Color(255, 255, 000);
}

Color getColor(const string& color)
{
	return colors[color];
}