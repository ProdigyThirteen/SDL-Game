#include "InputHandler.h"
#include <stdio.h>
#include <vector>

bool inputHandler::m_mouseButtonStates[MOUSEBUTTON_NUM_ITEMS];
Vec2* inputHandler::m_mousePosition;
const Uint8* inputHandler::m_currentKeystates;
Uint8* inputHandler::m_lastKeystates;

bool inputHandler::init()
{
	printf("Input Handler Initialising...\n");
	for (int i = 0; i < MOUSEBUTTON_NUM_ITEMS; i++)
		m_mouseButtonStates[i] = false;
	
	m_mousePosition = new Vec2(0, 0);
	m_currentKeystates = SDL_GetKeyboardState(0);
	m_lastKeystates = new Uint8[SDL_NUM_SCANCODES];

	return true;
}

void inputHandler::cleanup()
{
	printf("Input Handler Cleaning Up...\n");
	delete[] m_lastKeystates;
	delete m_mousePosition;
}

void inputHandler::update()
{
	SDL_memcpy(m_lastKeystates, m_currentKeystates, SDL_NUM_SCANCODES);
}

bool inputHandler::onKeyDown(SDL_Scancode key)
{
	if (m_currentKeystates[key] == 1 && m_lastKeystates[key] == 0)
		return true;
	return false;
}

bool inputHandler::onKeyUp(SDL_Scancode key)
{
	if (m_currentKeystates[key] == 0 && m_lastKeystates[key] == 1)
		return true;
	return false;
}

bool inputHandler::isKeyDown(SDL_Scancode key)
{
	if (m_currentKeystates)
	{
		if (m_currentKeystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void inputHandler::onMouseMove(SDL_Event& event)
{
	m_mousePosition->x = event.motion.x;
	m_mousePosition->y = event.motion.y;
}

void inputHandler::onMouseButtonDown(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = true;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = true;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{	
		m_mouseButtonStates[RIGHT] = true;
	}
}

void inputHandler::onMouseButtonUp(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = false;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = false;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = false;
	}
}
