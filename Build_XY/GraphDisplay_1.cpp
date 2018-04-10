#include "GraphDisplay.h"

GraphDisplay::GraphDisplay(int sWidth, int sHeight, const vector<pair<FuncYX, Color>>& funcs, Color cBackground, Color cAxes)
{
	this->sWidth = sWidth;
	this->sHeight = sHeight;
	this->funcs = funcs;
	this->cBackground = cBackground;
	this->cAxes = cAxes;
	offsetX = 0;
	offsetY = 0;
	scale = defaultSegSize;
	segSize = defaultSegSize;
	axesStep = 1;
	axesPrecision = 0;
}

void GraphDisplay::update(double deltaTime)
{
	if (Keyboard::isKeyPressed(Keyboard::Up) || mouseWheelStatus == 1)
	{
		scale += scale * deltaTime * zoomSens;
		if (scale > maxScale)
			scale = maxScale;
		while (segSize * 2 <= scale)
		{
			axesStep /= 2;
			if (axesStep < 1)
				axesPrecision++;
			segSize *= 2;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) || mouseWheelStatus == -1)
	{
		scale -= scale * deltaTime * zoomSens;
		if (scale < minScale)
			scale = minScale;
		while (segSize / 2 >= scale)
		{
			axesStep *= 2;
			if (axesStep <= 1)
				axesPrecision--;
			segSize /= 2;
		}
	}
	dragging();
	if (Keyboard::isKeyPressed(Keyboard::W))
		offsetY += deltaTime / scale * moveSens;
	if (Keyboard::isKeyPressed(Keyboard::S))
		offsetY -= deltaTime / scale * moveSens;
	if (Keyboard::isKeyPressed(Keyboard::A))
		offsetX -= deltaTime / scale * moveSens;
	if (Keyboard::isKeyPressed(Keyboard::D))
		offsetX += deltaTime / scale * moveSens;
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
	//TODO: Координаты курсора для нескольких графиков
	//cursorCoord();
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
		}
		double deltaTime = clock.restart().asMicroseconds();
		update(deltaTime);
		display();
	}
}