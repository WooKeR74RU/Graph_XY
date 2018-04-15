#pragma once
#include "Utilities.h"

class InputSystem
{
	const RenderWindow* window;
	enum KeyState { FREE, DOWN, PRESSED, UP };
	array<KeyState, Keyboard::KeyCount> keyboardKeysState;
	array<KeyState, Mouse::ButtonCount> mouseButtonsState;
public:
	bool isMouseMoved;
	bool isMouseEntered;
	bool isMouseLeft;
	int mouseX;
	int mouseY;
	bool isMouseWheelScrolled;
	float mouseWheelDelta;
	InputSystem();
	InputSystem(const RenderWindow& window);
	void keyboardKeyPressed(Keyboard::Key key);
	void keyboardKeyReleased(Keyboard::Key key);
	void mouseButtonPressed(Mouse::Button button);
	void mouseButtonReleased(Mouse::Button button);
	bool isKeyboardKeyPressed(Keyboard::Key key) const;
	bool isKeyboardKeyDown(Keyboard::Key key) const;
	bool isKeyboardKeyUp(Keyboard::Key key) const;
	bool isMouseButtonPressed(Mouse::Button button) const;
	bool isMouseButtonDown(Mouse::Button button) const;
	bool isMouseButtonUp(Mouse::Button button) const;
	void refresh();
};