#include "Sounds.h"
#include <iostream>

std::map<std::string, Mix_Chunk*> Sounds::m_sounds;

bool Sounds::init()
{
	if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)
	{
		printf("Mix_Init Error: %s", Mix_GetError());
		return false;
	}
	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("Failed to open audio channel. SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	return true;
}

void Sounds::cleanup()
{
	for (auto it = m_sounds.begin(); it != m_sounds.end(); ++it)
	{
		Mix_FreeChunk(it->second);
	}
	m_sounds.clear();
}

bool Sounds::loadSound(std::string path, std::string soundID)
{
	Mix_Chunk* pChunk = Mix_LoadWAV(path.c_str());
	if (!pChunk)
	{
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	m_sounds[soundID] = pChunk;
	return true;
}

void Sounds::playSound(std::string soundID)
{
	Mix_PlayChannel(-1, m_sounds[soundID], 0);
}