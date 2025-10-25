#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include <vector>

#include "Grid.h"
#include "PlayerCursor.h"
#include "LevelLoader.h"

class Game
{
private:
	Grid* grid = nullptr;
	PlayerCursor* player = nullptr;

	std::vector<std::string> levelFiles;
	bool gameOver = false;
	unsigned int currentLevelIndex = 0;

	void loadLevelManifest(const std::string& levelManifestFilename);
	void loadNextLevel();

	static Direction charToDirection(char inputChar);
	bool handleInput();
	void checkGameState();

public:
	Game(const std::string& levelManifestFilename);
	~Game();

	void run();
};

#endif
