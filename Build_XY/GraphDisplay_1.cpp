#include "GraphDisplay.h"

GraphDisplay::GraphDisplay(int sWidth, int sHeight, const FuncYX& func, Color cBackground, Color cAxes, Color cGraph)
{
	this->sWidth = sWidth;
	this->sHeight = sHeight;
	this->func = func;
	this->cBackground = cBackground;
	this->cAxes = cAxes;
	this->cGraph = cGraph;
	offsetX = 0;
	offsetY = 0;
	scale = 50;
}

void GraphDisplay::setView(double offsetX, double offsetY, double scale)
{
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->scale = scale;
}

void GraphDisplay::update(double deltaTime)
{
	dragging(deltaTime);
	if (Keyboard::isKeyPressed(Keyboard::Up) || mouseWheelStatus == 1)
	{
		scale += scale * deltaTime / 2e5;
		if (scale > 500)
			scale = 500;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) || mouseWheelStatus == -1)
	{
		scale -= scale * deltaTime / 2e5;
		if (scale < 50)
			scale = 50;
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
		offsetY += deltaTime / 1e3 / scale;
	if (Keyboard::isKeyPressed(Keyboard::S))
		offsetY -= deltaTime / 1e3 / scale;
	if (Keyboard::isKeyPressed(Keyboard::A))
		offsetX -= deltaTime / 1e3 / scale;
	if (Keyboard::isKeyPressed(Keyboard::D))
		offsetX += deltaTime / 1e3 / scale;
}

void GraphDisplay::display()
{
	window.clear(cBackground);
	drawAxes();
	cursorCoord();
	construct();
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

void GraphDisplay::dragging(double deltaTime)
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