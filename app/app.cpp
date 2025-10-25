// app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "Game.h"

int main()
{
	const std::string levelManifestFilename = "levels/level-manifest.txt";

	try {
		Game game(levelManifestFilename);
		game.run();
	}
	catch (...) {
		std::cerr << "Game crashed :(" << std::endl;
		return 1;
	}

	return 0;
}
