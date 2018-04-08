#pragma once
#include "Utilities.h"
#include "FuncYX.h"

class GraphDisplay
{
private:
	RenderWindow window;
	int sWidth;
	int sHeight;

	FuncYX func;
	Color cBackground;
	Color cAxes;
	Color cGraph;

	void display();
	void update(double deltaTime);
	int mouseWheelStatus;
	void dragging(double deltaTime);

	double offsetX = 0;
	double offsetY = 0;
	double scale = 80; //pixels per unit
	bool onScreen(int cX, int cY) const;
	double toMathX(int x) const;
	double toMathY(int y) const;
	int toCrdX(double x) const;
	int toCrdY(double y) const;
	void construct();
	void drawAxes();
	void cursorCoord();
public:
	GraphDisplay(int sWidth, int sHeight, const FuncYX& func, Color cBackground, Color cAxes, Color cGraph);
	void setView(double offsetX, double offsetY, double scale);
	void run();
};