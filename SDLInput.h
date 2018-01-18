#ifndef SDLINPUT_H
#define SDLINPUT_H
#include <vector>
#include <SDL.h>
#include <iostream>
struct SDLKey
{
	SDLKey(int _key);
	int key;
	bool pressed;
};
class SDLInput
{
public:
	SDLInput() {}
	static void start();
	static void SetKey(int _key, bool _state);
	static bool GetKey(int _key);
private:
	static std::vector<SDLKey> keys;
	static bool init;
};

#endif