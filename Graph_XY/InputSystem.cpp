#include "InputSystem.h"

InputSystem::InputSystem()
{ }
InputSystem::InputSystem(const RenderWindow& window)
{
	this->window = &window;
	isMouseMoved = 0;
	isMouseEntered = 0;
	isMouseLeft = 0;
	mouseX = Mouse::getPosition(window).x;
	mouseY = Mouse::getPosition(window).y;
	isMouseWheelScrolled = 0;
	mouseWheelDelta = 0;
}

void InputSystem::keyboardKeyPressed(Keyboard::Key key)
{
	keyboardKeysState[key] = DOWN;
}
void InputSystem::keyboardKeyReleased(Keyboard::Key key)
{
	keyboardKeysState[key] = UP;
}
void InputSystem::mouseButtonPressed(Mouse::Button button)
{
	mouseButtonsState[button] = DOWN;
}
void InputSystem::mouseButtonReleased(Mouse::Button button)
{
	mouseButtonsState[button] = UP;
}

bool InputSystem::isKeyboardKeyPressed(Keyboard::Key key) const
{
	return keyboardKeysState[key] == DOWN || keyboardKeysState[key] == PRESSED;
}
bool InputSystem::isKeyboardKeyDown(Keyboard::Key key) const
{
	return keyboardKeysState[key] == DOWN;
}
bool InputSystem::isKeyboardKeyUp(Keyboard::Key key) const
{
	return keyboardKeysState[key] == UP;
}
bool InputSystem::isMouseButtonPressed(Mouse::Button button) const
{
	return mouseButtonsState[button] == DOWN || mouseButtonsState[button] == PRESSED;
}
bool InputSystem::isMouseButtonDown(Mouse::Button button) const
{
	return mouseButtonsState[button] == DOWN;
}
bool InputSystem::isMouseButtonUp(Mouse::Button button) const
{
	return mouseButtonsState[button] == UP;
}

void InputSystem::refresh()
{
	for (int i = 0; i < Keyboard::KeyCount; i++)
	{
		if (keyboardKeysState[i] == DOWN)
			keyboardKeysState[i] = PRESSED;
		if (keyboardKeysState[i] == UP)
			keyboardKeysState[i] = FREE;
	}
	for (int i = 0; i < Mouse::ButtonCount; i++)
	{
		if (mouseButtonsState[i] == DOWN)
			mouseButtonsState[i] = PRESSED;
		if (mouseButtonsState[i] == UP)
			mouseButtonsState[i] = FREE;
	}
	isMouseMoved = 0;
	isMouseEntered = 0;
	isMouseLeft = 0;
	isMouseWheelScrolled = 0;
	mouseWheelDelta = 0;
}