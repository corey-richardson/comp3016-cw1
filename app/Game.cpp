#include "Game.h"
#include <fstream>
#include <iostream>

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


void Game::deletePlayerCursor() {
	if (player != nullptr) {
		delete player;
		player = nullptr;
	}
}


void Game::deleteGrid() {
	if (grid != nullptr) {
		delete grid;
		grid = nullptr;
	}
}


void Game::cleanupLevel() {
	this->deletePlayerCursor();
	this->deleteGrid();
}


void Game::resetCurrentLevelState() {
	if (grid == nullptr) {
		return;
	}

	grid->reset();
	this->deletePlayerCursor();
	this->player = new PlayerCursor(*grid);
}


void Game::loadNextLevel() {
	this->cleanupLevel();

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


Game::~Game() {
	this->cleanupLevel();
}


bool Game::handleInput() {
	char input;
	std::cout << "\nMove (WASD): ";

	if (!(std::cin >> input)) {
		gameOver = true;
		return false;
	}

	input = std::tolower(input);

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
