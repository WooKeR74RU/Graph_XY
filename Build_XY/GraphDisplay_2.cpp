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

void GraphDisplay::graphMark()
{
	static const int markPrecision = 6;
	static const int dotRadius = 4;
	static vector<CircleShape> dots;
	static bool INIT = 0;
	if (!INIT)
	{
		dots.resize(funcs.size());
		for (int i = 0; i < funcs.size(); i++)
		{
			dots[i].setFillColor(funcs[i].second);
			dots[i].setRadius(dotRadius);
		}
		INIT = 1;
	}
	if (!isCursorInWindow(window))
		return;
	bool isArgX = funcs[curMark].first.argument == "x";
	int cArg = isArgX ? Mouse::getPosition(window).x : Mouse::getPosition(window).y;
	double mArg = isArgX ? toMathX(cArg) : toMathY(cArg);
	funcs[curMark].first.setArgument(mArg);
	double mRes;
	if (!funcs[curMark].first.consider(mRes))
		mRes = NAN;
	string strX = dtos(isArgX ? mArg : mRes, markPrecision);
	string strY = dtos(isArgX ? mRes : mArg, markPrecision);
	window.setTitle(string("Graph_XY |") + string(" ID: ") + to_string(curMark + 1) + string(" X: ") + strX + string(" Y: ") + strY);
	if (isnan(mRes))
		return;
	int cDotX = isArgX ? cArg : toCrdX(mRes);
	int cDotY = isArgX ? toCrdY(mRes) : cArg;
	bool isOnScreen = 0 <= cDotX + dotRadius && cDotX - dotRadius < sWidth && 0 <= cDotY + dotRadius && cDotY - dotRadius < sHeight;
	if (isOnScreen)
	{
		dots[curMark].setPosition(cDotX - dotRadius, cDotY - dotRadius);
		window.draw(dots[curMark]);
	}
}

void GraphDisplay::construct(Function& func, Color color)
{
	bool isArgX = func.argument == "x";
	for (int cArg = 0; cArg < (isArgX ? sWidth : sHeight); cArg++)
	{
		double mArg1 = isArgX ? toMathX(cArg) : toMathY(cArg);
		double mRes1;
		func.setArgument(mArg1);
		if (!func.consider(mRes1) || isnan(mRes1))
			continue;
		double mArg2 = isArgX ? toMathX(cArg + 1) : toMathY(cArg + 1);
		double mRes2;
		func.setArgument(mArg2);
		if (!func.consider(mRes2) || isnan(mRes2))
			continue;
		int cRes1 = isArgX ? toCrdY(mRes1) : toCrdX(mRes1);
		int cRes2 = isArgX ? toCrdY(mRes2) : toCrdX(mRes2);
		if (!onScreen(isArgX ? cArg : cRes1, isArgX ? cRes1 : cArg) && !onScreen(isArgX ? cArg : cRes2, isArgX ? cRes2 : cArg))
			continue;
		if (cRes2 < cRes1)
			swap(cRes1, cRes2);
		cRes1 = max(cRes1, 0);
		cRes2 = min(cRes2, isArgX ? sHeight - 1 : sWidth - 1);
		line(window, isArgX ? cArg : cRes1, isArgX ? cRes1 : cArg, isArgX ? cArg : cRes2, isArgX ? cRes2 : cArg, color);
	}
}