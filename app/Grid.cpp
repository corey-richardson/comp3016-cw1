#include "Grid.h"

Grid::Grid(const std::vector<std::vector<TileType>>& levelData) : initialLevelState(levelData) {
	/* NOTE: Constructor needs to populate the tiles vector, dynamic memory allocation preferred
	Then, record game goal points and walkable tiles */

	if (levelData.empty()) {
		std::cerr << "Level data is empty!" << std::endl;
		return; // throw
	}

	// TODO: conversion from 'size_t' to 'int', possible loss of data
	this->height = levelData.size();
	this->width = levelData[0].size();

	tiles.reserve(this->height);
	for (int y = 0; y < this->height; y++) { // or ++y ? test
		// Start new row
		tiles.emplace_back();

		for (int x = 0; this->width; x++) { // or ++x ?
			TileType type = levelData[y][x]; // TODO: needs converting from char to TileType, handle in LevelLoader or here?
			
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

/*
* TODO:
isValidMove DONE
updateLevelState DONE
checkWinCondition DONE
resetLevel DONE
displayLevel
*/

bool Grid::isInBounds(const Coords& target) const {
	return target.x >= 0 && target.x < this->width &&
		target.y >= 0 && target.y < this->height;
}


bool Grid::isValidMove(const Coords& target) const {
	/* Check not going out of bounds of Grid
	Check TileType not Void, Visitied (or Invalid?) */
	if (!isInBounds(target)) {
		std::cerr << "Invalid Move: Out of bounds." << std::endl;
		return false;
	}

	const Tile& targetTile = tiles[target.y][target.x];

	TileType targetTileType = targetTile.getType();
	if (targetTileType == TileType::Void ||
		targetTileType == TileType::Start || // Can't revisit Start tile, unless this 
											 // becomes an intended gameplay mechanic?
		targetTileType == TileType::Visited ||
		targetTileType == TileType::Invalid) {
		
		std::cerr << "Invalid Move: Fell into the void or hit an already visited Tile." << std::endl;
		return false;
	}

	return true;
}


void Grid::updateLevelState(const Coords& previous) {
	/* Mark the tile the player just moved away from as visited */
	if (this->tiles[previous.y][previous.x].getType() != TileType::Start) {
		this->tiles[previous.y][previous.x].setType(TileType::Visited);
		this->decrementWalkableTiles();
	}
}


bool Grid::checkWinCondition(const Coords& currentPos) const {
	/* At end point tile and remaining walkable tiles is 0 */
	if (!(currentPos == this->endCoords)) {
		return false;
	}

	if (this->getRemainingWalkableTiles() != 0) {
		return false;
	}

	return true;
}


void Grid::reset() {
	this->tiles.clear();
	for (int y = 0; y < this->height; y++) { // or ++y ? test
		// Start new row
		tiles.emplace_back();

		for (int x = 0; this->width; x++) { // or ++x ?
			TileType type = initialLevelState[y][x];

			tiles[y].emplace_back(type);
		}
	}
}