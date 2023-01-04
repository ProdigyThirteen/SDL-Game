#pragma once

#include "SDL.h"
#include "Vec2.h"
#include <vector>

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2,
	MOUSEBUTTON_NUM_ITEMS = 3
};

class inputHandler
{
private:
	static bool m_mouseButtonStates[MOUSEBUTTON_NUM_ITEMS];
	
	static Vec2* m_mousePosition;
	static const Uint8* m_currentKeystates;
	static Uint8* m_lastKeystates;
	

public:
	static bool init();
	static void update();
	static void cleanup();

	static bool getMouseButtonState(int buttonNumber) { return m_mouseButtonStates[buttonNumber]; }
	static Vec2* getMousePosition() { return m_mousePosition; }

	
	//keyboard events
	static bool isKeyDown(SDL_Scancode key);
	static bool onKeyDown(SDL_Scancode key);
	static bool onKeyUp(SDL_Scancode key);

	//mouse events
	static void onMouseMove(SDL_Event& event);
	static void onMouseButtonDown(SDL_Event& event);
	static void onMouseButtonUp(SDL_Event& event);
};