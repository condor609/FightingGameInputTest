#include "SDLInput.h"

std::vector<SDLKey> SDLInput::keys;
bool SDLInput::init;

SDLKey::SDLKey(int _key)
{
	key = _key;
	pressed = false;
}

void SDLInput::start()
{
	if (!init)
	{
		keys.push_back(SDLKey(SDLK_w));
		keys.push_back(SDLKey(SDLK_a));
		keys.push_back(SDLKey(SDLK_s));
		keys.push_back(SDLKey(SDLK_d));
		keys.push_back(SDLKey(SDLK_LEFT));
		keys.push_back(SDLKey(SDLK_RIGHT));
		keys.push_back(SDLKey(SDLK_UP));
		keys.push_back(SDLKey(SDLK_DOWN));
		init = true;
	}
}

void SDLInput::SetKey(int _key, bool _state)
{
	for (SDLKey key : keys)
	{
		if (key.key = _key) key.pressed = _state;
	}
}

bool SDLInput::GetKey(int _key)
{
	if (init)
	{
		for (SDLKey key : keys)
		{
			if (key.key == _key) return key.pressed;
		}
		std::cerr << "Invalid Key \n";
		return false;
	}
	std::cerr << "Inputs not yet initialised \n";
	return false;
}