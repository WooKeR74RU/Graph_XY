#include "GraphDisplay.h"

bool GraphDisplay::onScreen(int cX, int cY) const
{
	return 0 <= cX && cX < sWidth && 0 <= cY && cY < sHeight;
}
double GraphDisplay::toMathX(int x) const
{
	return (x - sWidth / 2) / scale + offsetX;
}
double GraphDisplay::toMathY(int y) const
{
	return -(y - sHeight / 2) / scale + offsetY;
}
int GraphDisplay::toCrdX(double x) const
{
	return (x - offsetX) * scale + sWidth / 2;
}
int GraphDisplay::toCrdY(double y) const
{
	return -(y - offsetY) * scale + sHeight / 2;
}

void GraphDisplay::drawAxes()
{
	static const int markupLength = 4;
	static Font markupFont;
	static Text markupText;
	static bool INIT = 0;
	if (!INIT)
	{
		markupFont.loadFromFile("Fonts/calibri.ttf");
		markupText.setFont(markupFont);
		markupText.setCharacterSize(15);
		markupText.setFillColor(cAxes);
		INIT = 1;
	}
	
	int x0 = toCrdX(0);
	x0 = max(x0, markupLength);
	x0 = min(x0, sWidth - 1 - markupLength);
	line(window, x0, 0, x0, sHeight - 1, cAxes);
	double stY = getCloseLowerNum(toMathY(sHeight - 1), axesStep);
	for (double curY = stY; curY <= toMathY(0); curY += axesStep)
	{
		if (curY)
		{
			line(window, x0 - markupLength, toCrdY(curY), x0 + markupLength, toCrdY(curY), cAxes);
			markupText.setString(dtos(curY, axesPrecision));
			int textX = x0 - 2 * markupLength - markupText.getLocalBounds().left - markupText.getLocalBounds().width;
			if (x0 < sWidth / 5)
				textX = x0 + 2 * markupLength - markupText.getLocalBounds().left + 1;
			int textY = toCrdY(curY) - markupText.getLocalBounds().top - markupText.getLocalBounds().height / 2;
			markupText.setPosition(textX, textY);
			window.draw(markupText);
		}
	}
	int y0 = toCrdY(0);
	y0 = max(y0, markupLength);
	y0 = min(y0, sHeight - 1 - markupLength);
	line(window, 0, y0, sWidth - 1, y0, cAxes);
	double stX = getCloseLowerNum(toMathX(0), axesStep);
	for (double curX = stX; curX < toMathX(sWidth - 1); curX += axesStep)
	{
		if (curX)
		{
			line(window, toCrdX(curX), y0 - markupLength, toCrdX(curX), y0 + markupLength, cAxes);
			markupText.setString(dtos(curX, axesPrecision));
			int textX = toCrdX(curX) - markupText.getLocalBounds().left - markupText.getLocalBounds().width / 2;
			int textY = y0 + 2 * markupLength - markupText.getLocalBounds().top + 1;
			if (y0 > sHeight * 4 / 5)
				textY = y0 - 2 * markupLength - markupText.getLocalBounds().top - markupText.getLocalBounds().height;
			markupText.setPosition(textX, textY);
			window.draw(markupText);
		}
	}
}

//void GraphDisplay::cursorCoord()
//{
//	static const int dotRadius = 4;
//	static CircleShape dot;
//	static bool INIT = 0;
//	if (!INIT)
//	{
//		dot.setFillColor(cGraph);
//		dot.setRadius(dotRadius);
//		INIT = 1;
//	}
//
//	if (!isCursorInWindow(window))
//		return;
//	int cX = Mouse::getPosition(window).x;
//	double mX = toMathX(cX);
//	double mY;
//	if (!func.consider(mY, mX) || isnan(mY))
//		mY = NAN;
//	window.setTitle(string("Graph_XY") + string(" | ") + string("x: ") + to_string(mX) + string(" y: ") + to_string(mY));
//	dot.setPosition(cX - dotRadius, toCrdY(mY) - dotRadius);
//	window.draw(dot);
//}

void GraphDisplay::construct(const FuncYX& func, Color color)
{
	for (int cX = 0; cX < sWidth; cX++)
	{
		double mX1 = toMathX(cX);
		double mY1;
		if (!func.consider(mY1, mX1) || isnan(mY1))
			continue;
		double mX2 = toMathX(cX + 1);
		double mY2;
		if (!func.consider(mY2, mX2) || isnan(mY2))
			continue;
		int cY1 = toCrdY(mY1);
		int cY2 = toCrdY(mY2);
		if (!onScreen(cX, cY1) && !onScreen(cX, cY2))
			continue;
		if (cY2 < cY1)
			swap(cY1, cY2);
		cY1 = max(cY1, 0);
		cY2 = min(cY2, sHeight - 1);
		line(window, cX, cY1, cX, cY2, color);
	}
}