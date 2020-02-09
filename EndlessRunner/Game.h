#pragma once

#include "Screen.h"

class Game
{
	Screen screen;

	void Init();
public:
	void Run();
	Game();
	~Game();
};

