// app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "Game.h"
#include "LevelLoader.h"

int main()
{
	const std::string levelManifestFilename = "levels/level-manifest.txt";

	try {
		Game game(levelManifestFilename);
		game.run();
	}
	catch (const LevelLoadException& e) {
		std::cerr << "A required game file could not be loaded!" << std::endl;
		std::cerr << e.what() << std::endl;
		return 2;
	}
	catch (const std::runtime_error& e) {
		std::cerr << "A runtime error caused an exception!" << std::endl;
		std::cerr << e.what() << std::endl;
		return 3;
	}
	catch (const std::exception& e) {
		std::cerr << "An unknown error caused an exception!" << std::endl;
		std::cerr << e.what() << std::endl;
		return 4;
	}
	catch (...) {
		std::cerr << "Game crashed :(" << std::endl;
		return 1;
	}

	return 0;
}
