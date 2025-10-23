#pragma once
#ifndef  GRID_H
#define GRID_H

#include <vector>
#include <iostream>
#include "Tile.h"


struct Coords {
	int x;
	int y;

	// Compare whether two coordinates point to the same Tile
	// geeksforgeeks.org/cpp/operator-overloading-cpp/
	bool operator==(const Coords& target) const {
		return (x == target.x && y == target.y);
	}
};


class Grid {
private:
	std::vector<std::vector<Tile>> tiles;
	// Store the initial state of the level to be used for a reset
	std::vector<std::vector<TileType>> initialLevelState;

	int width = -1;
	int height = -1;

	Coords startCoords = { -1, -1 };
	Coords endCoords = { -1, -1 };

	// Win condition; sum of remaining Start, End and Walkable Tiles
	int remainingWalkableTiles = 0;
	void decrementWalkableTiles() {
		this->remainingWalkableTiles--;
	}

	bool isInBounds(const Coords& coords) const;

public:
	/* Constructor */
	// Recieves level data from the LevelLoader class
	Grid(const std::vector<std::vector<TileType>>& levelData);

	/* Getters */

	int getWidth() const { return this->width; }
	int getHeight() const { return this->height; }

	Coords getStartCoords() const { return this->startCoords; }
	Coords getEndCoords() const { return this->endCoords; }

	int getRemainingWalkableTiles() const { return this->remainingWalkableTiles;  }

	/* Game Logic Methods */
	bool isValidMove(const Coords& target) const;
	void updateLevelState(const Coords& previous);
	bool checkWinCondition(const Coords& currentPos) const;

	void resetLevel();

	void displayLevel() const;

};

#endif // ! GRID_H
