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
	inputHandler();
	~inputHandler() { delete m_mousePosition; };

	static inputHandler* s_pInstance;
	
	bool m_mouseButtonStates[MOUSEBUTTON_NUM_ITEMS];
	
	Vec2* m_mousePosition;
	const Uint8* m_currentKeystates = nullptr;
	Uint8* m_lastKeystates = nullptr;
	

public:
	static inputHandler* Get()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new inputHandler();
			return s_pInstance;
		}
		return s_pInstance;
	}

	void update();
	void cleanup();

	bool getMouseButtonState(int buttonNumber) { return m_mouseButtonStates[buttonNumber]; }
	Vec2* getMousePosition() { return m_mousePosition; }

	
	//keyboard events
	bool isKeyDown(SDL_Scancode key);
	bool onKeyDown(SDL_Scancode key);
	bool onKeyUp(SDL_Scancode key);

	//mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);
};