// app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "Game.h"
#include "RandomGame.h"
#include "LevelLoader.h"

int main(int argc, char *argv[])
{
	const std::string LEVEL_MANIFEST_FILENAME = "levels/level-manifest.txt";
	const std::string TEST_MANIFEST_FILENAME = "levels/test-manifest.txt";
	std::string manifest = LEVEL_MANIFEST_FILENAME;

	/* Use a VS Post-Build Event to copy levels over to Debug/Release build dir 
	Project Properties > Build Events > Post-Build Events 
	xcopy "$(ProjectDir)levels" "$(TargetDir)levels\" /s /i /y

	Then run from CLI: ./app --test
	*/
	if (argc > 1) {
		if (std::string(argv[1]) == "--test") {
			manifest = TEST_MANIFEST_FILENAME;
			std::cout << "Running in Test Mode." << std::endl;
			std::cout << "Loading files from: " << TEST_MANIFEST_FILENAME << std::endl;
		}
	}

	try {
		Game game;
		game.run(manifest);
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
