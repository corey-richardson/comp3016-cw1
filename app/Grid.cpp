#include "Grid.h"

/**
* @brief Constructs a Grid object from a 2D vector of TileType enum values. Called from LevelLoader.
* @param levelData A 2D vector of TileType values representing a level
*/
Grid::Grid(const std::vector<std::vector<TileType>>& levelData) : initialLevelState(levelData) {
	/* NOTE: Constructor needs to populate the tiles vector, dynamic memory allocation preferred
	Then, record game goal points and walkable tiles */

	if (levelData.empty() || levelData[0].empty()) {
		std::cerr << "Level data is empty or invalid!" << std::endl;
		return; // throw
	}

	// TODO: conversion from 'size_t' to 'int', possible loss of data
	this->height = levelData.size();
	this->width = levelData[0].size();

	tiles.reserve(this->height);

	/* size_t should be preferred over int when indexing into an STL vector
	unsigned int *could* be used to avoid conversion requirement BUT may be smaller
	than size_t on some architectures */

	for (size_t y = 0; y < this->height; ++y) { // ++y avoids unnecassary copies
		// Start new row
		tiles.emplace_back();

		for (size_t x = 0; x < this->width; ++x) {
			TileType type = levelData[y][x];
			
			tiles[y].emplace_back(type);

			// Track the Start and End points positions
			if (type == TileType::Start) {
				this->startCoords = { x, y };
				this->remainingWalkableTiles++;
			}
			else if (type == TileType::End) {
				this->endCoords = { x, y };
				this->remainingWalkableTiles++;
			}
			else if (type == TileType::Walkable) {
				this->remainingWalkableTiles++;
			}

		}
	}
}


/**
* @brief Private helper method that checks a co-ordinate is within bounds of grid
* @param target A set of co-ordinates to validate
* @return True if the co-ordinates are valid, else false
*/
bool Grid::isInBounds(const Coords& target) const {
	return target.x >= 0 && target.x < this->width &&
		target.y >= 0 && target.y < this->height;
}


/**
* @brief Validates whether a move is allowed or is a game fail-condition
* 1. Check move doesn't go out of bounds of the Grid based on width and height
* 2. Checks that the move is to a Tile that isWalkable (not Void or Visited)
* 3. Checks that the move isn't revisiting the Start Tile
* @param target The co-ordinate of the intended move
* @return True if the move is valid, else false
*/
bool Grid::isValidMove(const Coords& target) const {
	// 1
	if (!isInBounds(target)) {
		std::cerr << "Invalid Move: Out of bounds." << std::endl;
		return false;
	}

	const Tile& targetTile = tiles[target.y][target.x];

	// 2
	if (!targetTile.isWalkable()) {
		std::cerr << "Invalid Move: Fell into the void or hit an already visited Tile." << std::endl;
		return false;
	}

	// 3
	// Can't revisit Start tile, unless this becomes an intended gameplay mechanic?
	if (targetTile.getType() == TileType::Start) {
		std::cerr << "Invalid Move: Can't revisit the Start Tile." << std::endl;
		return false;
	}

	return true;
}


/**
* @brief Mark the tile the player just moved away from as visited
* @param previous The co-ordinate of the previously occupied tile
*/
void Grid::updateLevelState(const Coords& previous) {
	if (this->tiles[previous.y][previous.x].getType() != TileType::Start) {
		this->tiles[previous.y][previous.x].setType(TileType::Visited);
		this->decrementWalkableTiles();
	}
}


/**
* @brief Check if the win conditions have been met
* 1. The currentPos matches the endCoords of the level
* 2. All walkable tiles have been visited
* @param currentPos The co-ordinate of the current position
* @return True if the win conditions have been reached, else guarding falses
*/
bool Grid::checkWinConditions(const Coords& currentPos) const {
	if (!(currentPos == this->endCoords)) { // Uses overloaded '==' operator
		return false;
	}

	if (this->getRemainingWalkableTiles() != 0) {
		return false;
	}

	return true;
}


/**
* @brief Resets the Grid to its initial state for a level restart
*/
void Grid::reset() {
	this->tiles.clear();
	for (size_t y = 0; y < this->height; ++y) {
		// Start new row
		tiles.emplace_back();

		for (size_t x = 0; x < this->width; ++x) {
			TileType type = initialLevelState[y][x];

			tiles[y].emplace_back(type);
		}
	}
}


/**
* @brief Prints the current state of the game grid to the console
*/
void Grid::display() const {
	for (size_t y = 0; y < this->height; ++y) {
		for (size_t x = 0; x < this->width; ++x) {
			char cell = Tile::getDisplayChar(tiles[y][x].getType());
			std::cout << cell << " ";
		}
		std::cout << "\n";
	}
}
