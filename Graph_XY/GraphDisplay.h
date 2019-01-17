#pragma once
#include "Utilities.h"
#include "InputSystem.h"
#include "Function.h"

class GraphDisplay
{
private:
	RenderWindow window;
	InputSystem input;
	int sWidth;
	int sHeight;

	vector<pair<Function, Color>> funcs;
	Color cBackground;
	Color cAxes;

	void update(double deltaTime);
	void dragging();

	void display();
	void drawAxes();
	void construct(Function& func, Color color);
	void graphMark();
	int curMark;

	static const int defaultSegSize = 128;
	double scale; //pixels per unit
	double axesStep;
	int axesPrecision;
	double offsetX;
	double offsetY;

	bool onScreen(int cX, int cY) const;
	double toMathX(int x) const;
	double toMathY(int y) const;
	int toCrdX(double x) const;
	int toCrdY(double y) const;

public:
	GraphDisplay(int sWidth, int sHeight, const vector<pair<Function, Color>>& funcs, Color cBackground, Color cAxes);
	void setView(double offsetX, double offsetY);
	void start();
};