
#include <iostream>
#include "SDL.h"
#include "SdlManager.h"
#include "Game.h"

int main(int argc, char* args[])
{
	try {
		SdlManager sdlManager;
		sdlManager.Init();

		Game game;
		game.Run();
	}
	catch (exception e)
	{
		cout << e.what() << endl;
		throw;
	}

	return 0;
}
