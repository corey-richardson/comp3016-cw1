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
protected:
	Grid* grid = nullptr;
	PlayerCursor* player = nullptr;

	std::vector<std::string> levelFiles;
	bool gameOver = false;
	unsigned int currentLevelIndex = 0;

	void deletePlayerCursor();
	void deleteGrid();
	void cleanupLevel();
	void resetCurrentLevelState();

	virtual void loadLevelManifest(const std::string& levelManifestFilename);
	virtual void loadNextLevel(unsigned int attempts = 0);

	const unsigned int MAX_LOAD_ATTEMPTS = 10;

	static Direction charToDirection(char inputChar);
	bool handleInput();
	void checkGameState();
	virtual void onLevelSolved();

	void initialise(const std::string& levelManifestFilename);

public:
	Game();
	~Game();

	void run(const std::string& levelManifestFilename);
};

#endif
