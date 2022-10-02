#pragma once

#include "SDL.h"
#include "Vec2.h"
#include <vector>

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class inputHandler
{
private:
	inputHandler();
	~inputHandler() { };

	static inputHandler* s_pInstance;
	
	std::vector<bool> m_mouseButtonStates;
	Vec2* m_mousePosition;
	const Uint8* m_keystates;
	
	//keyboard events
	void onKeyDown();
	void onKeyUp();

	//mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

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

	bool isKeyDown(SDL_Scancode key);
};