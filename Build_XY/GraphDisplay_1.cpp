#include "GraphDisplay.h"

GraphDisplay::GraphDisplay(int sWidth, int sHeight, const vector<pair<Function, Color>>& funcs, Color cBackground, Color cAxes)
{
	this->sWidth = sWidth;
	this->sHeight = sHeight;
	this->funcs = funcs;
	this->cBackground = cBackground;
	this->cAxes = cAxes;
	offsetX = 0;
	offsetY = 0;
	scale = defaultSegSize;
	axesStep = 1;
	axesPrecision = 0;
	curMark = 0;
}

void GraphDisplay::setView(double offsetX, double offsetY)
{
	this->offsetX = offsetX;
	this->offsetY = offsetY;
}

void GraphDisplay::update(double deltaTime)
{
	if (Keyboard::isKeyPressed(Keyboard::Up) || mouseWheelStatus == 1)
	{
		scale += scale * deltaTime * zoomSens;
		if (scale > maxScale)
			scale = maxScale;
		while (defaultSegSize / axesStep < scale)
		{
			axesStep /= 2;
			if (axesStep < 1)
				axesPrecision++;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) || mouseWheelStatus == -1)
	{
		scale -= scale * deltaTime * zoomSens;
		if (scale < minScale)
			scale = minScale;
		while (scale * 2 <= defaultSegSize / axesStep)
		{
			if (axesStep < 1)
				axesPrecision--;
			axesStep *= 2;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::W))
		offsetY += deltaTime / scale * moveSens;
	if (Keyboard::isKeyPressed(Keyboard::S))
		offsetY -= deltaTime / scale * moveSens;
	if (Keyboard::isKeyPressed(Keyboard::A))
		offsetX -= deltaTime / scale * moveSens;
	if (Keyboard::isKeyPressed(Keyboard::D))
		offsetX += deltaTime / scale * moveSens;
	dragging();

	if (isKeyDown(Keyboard::Num1))
	{
		curMark--;
		if (curMark == -1)
			curMark = funcs.size() - 1;
	}
	if (isKeyDown(Keyboard::Num2))
	{
		curMark++;
		if (curMark == funcs.size())
			curMark = 0;
	}
}

void GraphDisplay::dragging()
{
	static int prevX;
	static int prevY;
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		int deltaX = Mouse::getPosition().x - prevX;
		int deltaY = Mouse::getPosition().y - prevY;
		offsetX -= deltaX / scale;
		offsetY += deltaY / scale;
	}
	prevX = Mouse::getPosition().x;
	prevY = Mouse::getPosition().y;
}

void GraphDisplay::display()
{
	window.clear(cBackground);
	drawAxes();
	graphMark();
	for (int i = 0; i < funcs.size(); i++)
		construct(funcs[i].first, funcs[i].second);
	window.display();
}

void GraphDisplay::run()
{
	window.create(VideoMode(sWidth, sHeight), "Graph_XY", Style::Close);
	window.setVerticalSyncEnabled(true);
	Clock clock;
	while (window.isOpen())
	{
		mouseWheelStatus = 0;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseWheelScrolled)
				mouseWheelStatus = event.mouseWheelScroll.delta;
			if (event.type == Event::KeyReleased)
				keyUp(event.key.code);
		}
		double deltaTime = clock.restart().asMicroseconds();
		update(deltaTime);
		display();
	}
}