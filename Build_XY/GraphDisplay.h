#pragma once
#include "Utilities.h"
#include "FuncYX.h"

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

	vector<pair<FuncYX, Color>> funcs;
	Color cBackground;
	Color cAxes;

	void display();
	void update(double deltaTime);
	int mouseWheelStatus;
	void dragging();

	double scale; //pixels per unit
	double segSize;
	double axesStep;
	int axesPrecision;
	double offsetX;
	double offsetY;

	bool onScreen(int cX, int cY) const;
	double toMathX(int x) const;
	double toMathY(int y) const;
	int toCrdX(double x) const;
	int toCrdY(double y) const;
	void construct(const FuncYX& func, Color color);
	void drawAxes();
	void cursorCoord();
public:
	GraphDisplay(int sWidth, int sHeight, const vector<pair<FuncYX, Color>>& funcs, Color cBackground, Color cAxes);
	void run();
};