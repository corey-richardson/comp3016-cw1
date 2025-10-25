#include "Game.h"
#include <fstream>
#include <iostream>

// Could the memory management issues I was having be resolved by unique_ptr?
// 
// """Using std::unique_ptr would make the Game class significantly safer and 
// easier to maintain by eliminating all manual memory management and 
// preventing potential memory leaks."""
//
// """std::unique\_ptr enforces RAII (Resource Acquisition Is Initialization), 
// guaranteeing memory is freed when the pointer goes out of scope"""


/**
* @brief Convert a keyboard input to a movement direction
* @param inputChar W/A/S/D, case-insensitive
* @return A Direction value
* @throws std::runtime_error if the input character does not correspond to an expected value. Handled in Game::handleInput
*/
Direction Game::charToDirection(char inputChar) {
	// https://en.cppreference.com/w/cpp/string/byte/tolower.html
	switch (std::tolower(inputChar)) {
	case 'w':
		return Direction::Up;
	case 'a':
		return Direction::Left;
	case 's':
		return Direction::Down;
	case 'd':
		return Direction::Right;
	default:
		throw std::runtime_error("No move.");
	}
}


/**
* @brief Loads a list of level filenames into a vector object from a manifest file
* @param levelManifestFilename The path to the manifest file containing the list
* @throws LevelLoadException if the manifest file cannot be opened or is empty
*/
void Game::loadLevelManifest(const std::string& levelManifestFilename) {
	std::ifstream file(levelManifestFilename);

	if (!file.is_open()) {
		throw LevelLoadException("Failed to open level manifest file: " + levelManifestFilename);
	}

	std::string line;

	while (std::getline(file, line)) {
		if (!line.empty()) {
			levelFiles.push_back(line);
		}
	}

	if (levelFiles.empty()) {
		throw LevelLoadException("Level manifest file is empty.");
	}

	file.close();
}


/**
* @brief Safely deletes the current instance of PlayerCursor
*/
void Game::deletePlayerCursor() {
	if (player != nullptr) {
		delete player;
		player = nullptr;
	}
}


/**
* @brief Safely deletes the current instance of Grid
*/
void Game::deleteGrid() {
	if (grid != nullptr) {
		delete grid;
		grid = nullptr;
	}
}


/**
* @brief Safely cleans up the current level by deleting the Grid and PlayerCursor instances
*/
void Game::cleanupLevel() {
	this->deletePlayerCursor();
	this->deleteGrid();
}


/**
* @brief Resets the Grid layout and resets the PlayerCursor location to the levels start
*/
void Game::resetCurrentLevelState() {
	if (grid == nullptr) {
		return;
	}

	grid->reset();
	this->deletePlayerCursor();
	this->player = new PlayerCursor(*grid);
}


/**
* @brief Loads the next level from the level manifest
* Clears any existing level resources from the memory
* @throws LevelLoadException if a level file fails to load. Attempts to skip and load the next level instead.
*/
void Game::loadNextLevel() {
	this->cleanupLevel();

	if (this->currentLevelIndex >= this->levelFiles.size()) {
		std::cout << "\n\nAll levels have been completed! Thank you for playing!" << std::endl;
		this->gameOver = true;
		return;
	}

	const std::string& filename = levelFiles[this->currentLevelIndex];

	try {
		std::vector<std::vector<TileType>> levelBlueprint = LevelLoader::loadLevel(filename);

		grid = new Grid(levelBlueprint);
		player = new PlayerCursor(*grid);
		gameOver = false;

		std::cout << "Loaded Level " << this->currentLevelIndex + 1 << std::endl;
		std::cout << "Visit all " << grid->getRemainingWalkableTiles() + 2 << " tiles to pass the level!" << std::endl;
	}
	catch (const LevelLoadException& e) {
		std::cerr << "Error Loading Level " << filename << ": " << e.what() << std::endl;

		currentLevelIndex++;
		loadNextLevel(); // try to load the next level and hope it aint broke
	}
}


/**
* @brief Constructs a Game instance and loads the first level to memory
* @param levelManifestFilename The path to the Level Manifest file
*/
Game::Game(const std::string& levelManifestFilename) {
	try {
		loadLevelManifest(levelManifestFilename);
		loadNextLevel();
	}
	catch (const std::exception& e) {
		std::cerr << "Game failed to construct :(" << std::endl;
		std::cerr << e.what() << std::endl;

		this->gameOver = true;
	}
}


/**
* @brief Desructor for the Game class
* Cleans up dynamically allocated resources used by the current level,
* such as the Grid and Player Cursor
*/
Game::~Game() {
	this->cleanupLevel();
}


/**
* @brief Handles the player input for movement or a player-induced level reset
* @return True if the game should continue (move is valid) or false if the input
* failed or move was invalid
*/
bool Game::handleInput() {
	char input;
	std::cout << "\nMove (WASD): ";

	if (!(std::cin >> input)) {
		gameOver = true;
		return false;
	}

	input = std::tolower(input);

	if (input == 'q') {
		std::cout << "Quitting game..." << std::endl;
		gameOver = true;
		return false;
	}

	if (input == 'r') {
		std::cout << "Resetting level..." << std::endl;

		this->resetCurrentLevelState();
		return true;
	}

	try {
		Direction moveDirection = charToDirection(input);
		bool moveSuccessful = player->move(moveDirection);

		if (!moveSuccessful) {
			this->resetCurrentLevelState();
		}
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
	}


	return true;
}


/**
* @brief Checks the current game state and reacts to level completion or 
* unsolvable states
*/
void Game::checkGameState() {
	if (grid->checkWinConditions(player->getCurrentPosition())) {
		std::cout << "Level " << this->currentLevelIndex + 1 << " solved!\n" << std::endl;

		this->currentLevelIndex++;
		loadNextLevel();
		return;
	}

	if (player->getCurrentPosition() == grid->getEndCoords() &&
		grid->getRemainingWalkableTiles() > 0) {
		std::cerr << "Unsolvable state reached! Resetting..." << std::endl;
		this->resetCurrentLevelState();
	}
}


/**
* @brief Runs the main game loop
* Displays the current grid state
* Processes player input
* Checks the game state for win-fail conditions
* Runs until game over or grid fails to load
*/
void Game::run() {
	while (!gameOver) {
		if (this->grid == nullptr) {
			break;
		}

		grid->display(player->getCurrentPosition());

		if (!handleInput()) {
			break;
		}

		if (!gameOver) {
			this->checkGameState();
		}
	}

	std::cout << "Game Over!" << std::endl;
}
