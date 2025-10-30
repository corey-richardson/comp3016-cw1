// app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <memory>

#include "Game.h"
#include "RandomGame.h"
#include "LevelLoader.h"


void displayMenu() {
	std::cout << "\n===================================" << std::endl;
	std::cout << "          PUZZLE PATH GAME         " << std::endl;
	std::cout << "===================================" << std::endl;
	std::cout << "1. Start Standard Game" << std::endl;
	std::cout << "2. Start Endless Random Game" << std::endl;
	std::cout << "3. Game and Rules Overview" << std::endl;
	std::cout << "4. Quit" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "Enter your choice (1-4): ";
}


void displayRules() {
	std::cout << "\n===================================" << std::endl;
	std::cout << "          GAME OVERVIEW           " << std::endl;
	std::cout << "===================================" << std::endl;
	std::cout << "OBJECTIVE: Visit every required tile on the grid to solve the level.\n" << std::endl;
	std::cout << "CONTROLS:" << std::endl;
	std::cout << " - W/A/S/D: Move Up, Left, Down, Right." << std::endl;
	std::cout << " - R: Reset the current level." << std::endl;
	std::cout << " - Q: Quit the game and return to the menu." << std::endl;
	std::cout << "\nTILE GUIDE:" << std::endl;
	std::cout << " - S: Start Position" << std::endl;
	std::cout << " - E: End Position (must be the last tile visited)" << std::endl;
	std::cout << " - .: Void Tiles (Non-walkable)" << std::endl;
	std::cout << " - #: Univisited Walkable Tile" << std::endl;
	std::cout << " - *: Visited Walkable Tile (Standard, or final visit for Multi-Visit)" << std::endl;
	std::cout << "\nMULTI-VISIT TILE GUIDE:" << std::endl;
	std::cout << "These tiles must be visited multiple times before they count as 'visited'." << std::endl;
	std::cout << " - 2: Requires 2 more visits." << std::endl;
	std::cout << " - 1: Requires 1 more visit." << std::endl;
	std::cout << "\nGAME MODES:" << std::endl;
	std::cout << " - Standard: Plays levels in manifest order." << std::endl;
	std::cout << " - Endless Random: Shuffles levels and cycles them infinitely." << std::endl;
	std::cout << "===================================\n" << std::endl;
}


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

	char choice = '0';
	while (choice != '4') {
		displayMenu();
		
		if (!(std::cin.get() >> choice)) { // .get() inky for first char
			std::cout << "Invalid Input. Please enter a number (1-4).\n" << std::endl;
			// https://stackoverflow.com/questions/257091/how-do-i-flush-the-cin-buffer
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			choice = '0';
			continue;
		}

		std::unique_ptr<Game> game = nullptr;

		switch (choice) {
			case '1': // Standard Game
				game = std::make_unique<Game>();
				game->run(manifest);
				break;
			case '2': // Random Endless
				game = std::make_unique<RandomGame>();
				game->run(manifest);
				break;
			case '3': // Rules and Game Overview
				displayRules();
				break;
			case '4': // Quit
			case 'q':
			case 'Q':
				std::cout << "\nQuitting...\n" << std::endl;
				return 0;

			default:
				std::cout << "Invalid Input. Please enter a number (1-4).\n" << std::endl;
				break;
		}
	}

	//try {
	//	Game game;
	//	game.run(manifest);
	//}
	//catch (const LevelLoadException& e) {
	//	std::cerr << "A required game file could not be loaded!" << std::endl;
	//	std::cerr << e.what() << std::endl;
	//	return 2;
	//}
	//catch (const std::runtime_error& e) {
	//	std::cerr << "A runtime error caused an exception!" << std::endl;
	//	std::cerr << e.what() << std::endl;
	//	return 3;
	//}
	//catch (const std::exception& e) {
	//	std::cerr << "An unknown error caused an exception!" << std::endl;
	//	std::cerr << e.what() << std::endl;
	//	return 4;
	//}
	//catch (...) {
	//	std::cerr << "Game crashed :(" << std::endl;
	//	return 1;
	//}

	return 0;
}
