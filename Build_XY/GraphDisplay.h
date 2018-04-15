#pragma once
#include "Utilities.h"
#include "Function.h"

static const double zoomSens = 1 / 2e5;
static const double moveSens = 1 / 1e3;

static const int defaultSegSize = 128;
static const int maxScale = sqr(defaultSegSize);
static const int minScale = 1;

class GraphDisplay
{
private:
	RenderWindow window;
	int sWidth;
	int sHeight;

	vector<pair<Function, Color>> funcs;
	Color cBackground;
	Color cAxes;

	void display();
	void update(double deltaTime);
	int mouseWheelStatus;
	void dragging();

	void drawAxes();
	void construct(Function& func, Color color);
	void graphMark();
	int curMark;

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
	void run();
};