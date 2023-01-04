#pragma once

#include <iostream>
#include <map>
#include "SDL_mixer.h"

class Sounds
{
private:
	static std::map<std::string, Mix_Chunk*> m_sounds;

public:
	static bool init();
	static void cleanup();
	static bool loadSound(std::string path, std::string soundID);
	static void playSound(std::string soundID);
};

