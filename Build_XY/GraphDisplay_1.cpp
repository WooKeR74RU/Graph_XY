#include "GraphDisplay.h"

GraphDisplay::GraphDisplay(int sWidth, int sHeight, const vector<pair<Function, Color>>& funcs, Color cBackground, Color cAxes)
{
	input = InputSystem(window);
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

void GraphDisplay::start()
{
	window.create(VideoMode(sWidth, sHeight), "Graph_XY", Style::Close);
	window.setVerticalSyncEnabled(1);
	window.setKeyRepeatEnabled(0);
	Clock clock;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
				input.keyboardKeyPressed(event.key.code);
			if (event.type == Event::KeyReleased)
				input.keyboardKeyReleased(event.key.code);
			if (event.type == Event::MouseMoved)
			{
				input.isMouseMoved = 1;
				input.mouseX = event.mouseMove.x;
				input.mouseY = event.mouseMove.y;
			}
			if (event.type == Event::MouseEntered)
				input.isMouseEntered = 1;
			if (event.type == Event::MouseLeft)
				input.isMouseLeft = 1;
			if (event.type == Event::MouseButtonPressed)
				input.mouseButtonPressed(event.mouseButton.button);
			if (event.type == Event::MouseButtonReleased)
				input.mouseButtonReleased(event.mouseButton.button);
			if (event.type == Event::MouseWheelScrolled)
			{
				input.isMouseWheelScrolled = 1;
				input.mouseWheelDelta = event.mouseWheelScroll.delta;
			}
		}
		double deltaTime = clock.restart().asMicroseconds();
		update(deltaTime);
		input.refresh();
		display();
	}
}

void GraphDisplay::update(double deltaTime)
{
	static const double zoomKeysSens = 1 / 2e5;
	static const double zoomWheelSens = zoomKeysSens * 3;
	static const double moveSens = 1 / 1e3;

	static const int maxScale = sqr(defaultSegSize);
	static const int minScale = 1;

	if (input.isKeyboardKeyPressed(Keyboard::Up) || input.mouseWheelDelta == 1)
	{
		if (input.isKeyboardKeyPressed(Keyboard::Up))
			scale += scale * deltaTime * zoomKeysSens;
		if (input.mouseWheelDelta == 1)
			scale += scale * deltaTime * zoomWheelSens;
		scale = min(scale, (double)maxScale);
		while (defaultSegSize / axesStep < scale)
		{
			axesStep /= 2;
			if (axesStep < 1)
				axesPrecision++;
		}
	}
	if (input.isKeyboardKeyPressed(Keyboard::Down) || input.mouseWheelDelta == -1)
	{
		if (input.isKeyboardKeyPressed(Keyboard::Down))
			scale -= scale * deltaTime * zoomKeysSens;
		if (input.mouseWheelDelta == -1)
			scale -= scale * deltaTime * zoomWheelSens;
		scale = max(scale, (double)minScale);
		while (scale * 2 <= defaultSegSize / axesStep)
		{
			if (axesStep < 1)
				axesPrecision--;
			axesStep *= 2;
		}
	}

	if (input.isKeyboardKeyPressed(Keyboard::W))
		offsetY += deltaTime / scale * moveSens;
	if (input.isKeyboardKeyPressed(Keyboard::A))
		offsetX -= deltaTime / scale * moveSens;
	if (input.isKeyboardKeyPressed(Keyboard::S))
		offsetY -= deltaTime / scale * moveSens;
	if (input.isKeyboardKeyPressed(Keyboard::D))
		offsetX += deltaTime / scale * moveSens;
	dragging();

	if (input.isKeyboardKeyDown(Keyboard::Num1))
	{
		curMark--;
		if (curMark == -1)
			curMark = funcs.size() - 1;
	}
	if (input.isKeyboardKeyDown(Keyboard::Num2))
	{
		curMark++;
		if (curMark == funcs.size())
			curMark = 0;
	}
}

void GraphDisplay::display()
{
	window.clear(cBackground);
	drawAxes();
	for (int i = 0; i < funcs.size(); i++)
		construct(funcs[i].first, funcs[i].second);
	graphMark();
	window.display();
}